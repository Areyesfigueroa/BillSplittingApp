#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "grouprecords.h"
#include <QTextStream>
#include <QMessageBox>
#include <functional>
#include "testfunctions.h"

//Default Static Values
int MainWindow::tableRow = 0;
int MainWindow::itemRow = 0;
int MainWindow::itemColumn = 0;

int MainWindow::paymentTableRow = 0;
int MainWindow::paymentItemRow = 0;
int MainWindow::paymentItemColumn = 0;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    //init
    createGrpDialog = 0;
    editGroupDialog = 0;
    friendsDialog = 0;
    billOptionsDialog = 0;

    //set up
    ui->setupUi(this);

    //FriendsTable Data
    itemPersonName = new QTableWidgetItem*[0];
    itemBill = new QTableWidgetItem*[0];
    itemGrpName = new QTableWidgetItem*[0];
    itemBillPayed = new QTableWidgetItem*[0];

    //Init Table
    tableWidget = ui->tableWidget;
    paymentTableWidget = ui->paymentTable;

    //Init Table Row and Column
    tableWidget->setColumnCount(4);
    tableWidget->setRowCount(0);

    //Init Payment Table Row and Column
    paymentTableWidget->setColumnCount(4);
    paymentTableWidget->setRowCount(0);

    //Init Table Header
    tableWidget->setHorizontalHeaderLabels(QStringList()<<"Group Name"<<"Group Size"<< "People" << "Total Bill");
    paymentTableWidget->setHorizontalHeaderLabels(QStringList()<<"Friends"<<"Group"<<"Bill"<<"Bill Payed");
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_plusButton_clicked()
{
    if(!createGrpDialog)//Creates one instance at a time
    {
        createGrpDialog = new CreateGroupDialog(this);
        connect(createGrpDialog, SIGNAL(updateList()), this, SLOT(onGroupCreated()));
    }
    createGrpDialog->show();
}

void MainWindow::on_editButton_clicked()
{
    if(!editGroupDialog)
    {
        editGroupDialog = new EditGroupDialog(this);
        connect(editGroupDialog, SIGNAL(groupChanged(std::string,int)),this,SLOT(onEditGroup(std::string,int)));
    }
    editGroupDialog->show();
}

void MainWindow::on_createBillButton_clicked()
{
    if(!billOptionsDialog)
    {
        billOptionsDialog = new BillOptionsDialog(this);
        connect(billOptionsDialog, SIGNAL(billCreated(float)), this, SLOT(onBillCreated(float))); //Updates the table
    }
    billOptionsDialog->comboBoxUpdate();
    billOptionsDialog->show();
}

void MainWindow::createFriendsDialogConnection()
{
    if(!friendsDialog)
    {
        friendsDialog = new FriendsDialog(this);
        connect(createGrpDialog, SIGNAL(addFriends(int)),friendsDialog,SLOT(onAddFriends(int)));
    }

    friendsDialog->show();
}

void MainWindow::onBillCreated(float totalBill)
{
    auto getTotalBill = [&totalBill]()->int{return totalBill;};
    updateBill(getTotalBill);
    updatePeopleOnBPTable();
        //call the new table function
}

//UpdateBill separately on bill payment table
void MainWindow::updateBillOnBPTable()
{

}

//updates the people on the bill payment table
void MainWindow::updatePeopleOnBPTable()
{
    GroupRecords *_instance = GroupRecords::instance();
    std::string groupName = _instance->groupRecords.fetchLatestRecord()->getGroupName();

    //Get group ref
    Group* group = _instance->groupRecords.fetchLatestRecord();

    //PeopleHelper variables
    size_t peopleCount = group->getPeopleCount();
    std::string personName;
    float bill;
    //go through the people records and get their names
    for(int i = 0; i < peopleCount; i++)
    {
        //increment row
         paymentTableRow++;
        //Setting Table Rows
         paymentTableWidget->setRowCount(paymentTableRow);

         Person* person = group->getPersonByIndex(i);
         personName = person->getPersonName();
         bill = person->getBillByKey(groupName);

         //Items need to be newed, new Items
         itemPersonName[i] = new QTableWidgetItem(QString::fromStdString(personName));
         itemGrpName[i] = new QTableWidgetItem(QString::fromStdString(groupName));
         itemBill[i] = new QTableWidgetItem(QString::number(bill));
         itemBillPayed[i] = new QTableWidgetItem(QString::fromStdString("no")); //have nothing to check at the moment

         //Setting Item Placement
         paymentTableWidget->setItem(paymentItemRow, paymentItemColumn, itemPersonName[i]); //Friends name
         paymentTableWidget->setItem(paymentItemRow, paymentItemColumn + 1, itemGrpName[i]); //increment column
         paymentTableWidget->setItem(paymentItemRow, paymentItemColumn + 2, itemBill[i]);
         paymentTableWidget->setItem(paymentItemRow, paymentItemColumn + 3, itemBillPayed[i]);

         //increment item rows
         paymentItemRow++;
    }
    //QTableWidgetClear, deletes pointer and the data in it
}

void MainWindow::updateBill(std::function<int()> getTotalBill) //passing lambda function
{
    QTableWidgetItem *itemGrpTotalBill = new QTableWidgetItem(QString::number(getTotalBill())); //insert lambda result onto QItem
    tableWidget->setItem(itemRow - 1, itemColumn + 3, itemGrpTotalBill); //display on the table
}

//connected
void MainWindow::onGroupCreated()
{
    createFriendsDialogConnection();
}

void MainWindow::onUpdateTableInfo()
{
    updateTable();
}

void MainWindow::updateTable()
{
    GroupRecords *_instance = GroupRecords::instance();

    std::string groupName = _instance->groupRecords.fetchLatestRecord()->getGroupName();
    int size = _instance->groupRecords.fetchLatestRecord()->getGroupSize();

    //Get group ref
    Group* group = _instance->groupRecords.fetchLatestRecord();

    //PeopleHelper variables
    size_t peopleCount = group->getPeopleCount();
    std::string personName = "";

    //go through the people records and get their names
    for(int i = 0; i < peopleCount; i++)
    {
         Person* person = group->getPersonByIndex(i);
         if(i > 0)
         {
             personName = personName +", "+ person->getPersonName();
         }
         else
         {
             personName = person->getPersonName();
         }
    }

    //Adding group name to listWidget
    ui->listWidget->addItem(QString::fromStdString(groupName));

    //increment row
    tableRow++;

    //Setting Table Rows
    tableWidget->setRowCount(tableRow);

    //Items need to be newed, new Items
    QTableWidgetItem *itemGrpName = new QTableWidgetItem(QString::fromStdString(groupName));
    QTableWidgetItem *itemGrpSize = new QTableWidgetItem(QString::number(size));
    QTableWidgetItem *itemGrpPeopleNames = new QTableWidgetItem(QString::fromStdString(personName));
    //QTableWidgetItem *itemGrpTotalBill = new QTableWidgetItem(QString::number(getTotalBill()));
    //Setting Item Placement
    tableWidget->setItem(itemRow, itemColumn, itemGrpName);
    tableWidget->setItem(itemRow, itemColumn + 1, itemGrpSize); //increment column
    tableWidget->setItem(itemRow, itemColumn + 2, itemGrpPeopleNames);
    //tableWidget->setItem(itemRow, itemColumn + 3, itemGrpTotalBill);
    //increment item rows
    itemRow++;
    //QTableWidgetClear, deletes pointer and the data in it
}


//connected
void MainWindow::onEditGroup(std::string newGrpName, int newGrpSize)
{
    int index = ui->listWidget->currentRow();
    QTextStream out(stdout);
    out << index;
    Group* currGroup = GroupRecords::instance()->groupRecords.fetchRecordsByIndex(index);

    //overwrite the Group
    currGroup->setGroupName(newGrpName);
    currGroup->setGroupSize(newGrpSize);
    ui->listWidget->currentItem()->setText(QString::fromStdString(currGroup->getGroupName()));
}



