#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "grouprecords.h"
#include <QTextStream>

//list lives here
//Check with teacher to choose the most optimal way of checking for duplicates
//For now do not enter duplicate groups.
//Check using a find

//Default Static Values
int MainWindow::tableRow = 0;
int MainWindow::itemRow = 0;
int MainWindow::itemColumn = 0;

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

    //Init Table
    tableWidget = ui->tableWidget;

    //Init Table Row and Column
    tableWidget->setColumnCount(4);
    tableWidget->setRowCount(0);

    //Init Table Header
    tableWidget->setHorizontalHeaderLabels(QStringList()<<"Group Name"<<"Group Size"<< "People" << "Total Bill");
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
        connect(billOptionsDialog, SIGNAL(billCreated()), this, SLOT(onBillCreated())); //Updates the table
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

void MainWindow::onBillCreated()
{
    //update table
}

//connected
void MainWindow::onGroupCreated()
{
    //getting instance
    //GroupRecords *_instance = GroupRecords::instance(); //Helps keep the code shorter

    //getting latest groupName
    /*Group* grp = _instance->groupRecords.fetchLatestRecord();
    std::string grpName = grp->getName();
    int grpSize = grp->getSize();*/
    createFriendsDialogConnection();
    //updateTable(grpName, grpSize); //wrong place, use when you create the group
}

void MainWindow::onUpdateTableInfo()
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

    //PeopleNames


    //Items need to be newed, new Items
    QTableWidgetItem *itemGrpName = new QTableWidgetItem(QString::fromStdString(groupName));
    QTableWidgetItem *itemGrpSize = new QTableWidgetItem(QString::number(size));
    QTableWidgetItem *itemGrpPeopleNames = new QTableWidgetItem(QString::fromStdString(personName));

    //Setting Item Placement
    tableWidget->setItem(itemRow, itemColumn, itemGrpName);
    tableWidget->setItem(itemRow, itemColumn + 1, itemGrpSize); //increment column
    tableWidget->setItem(itemRow, itemColumn + 2, itemGrpPeopleNames);
    //increment item rows
    itemRow++;
    //QTableWidgetClear, deletes pointer and the data in it
}

//DELETE FUNCTION
void MainWindow::updateTable(const std::string& name, int& size)
{
    //Adding name to listWidget
    ui->listWidget->addItem(QString::fromStdString(name));

    //increment row
    tableRow++;

    //Setting Table Rows
    tableWidget->setRowCount(tableRow);

    //PeopleNames


    //Items need to be newed, new Items
    QTableWidgetItem *itemGrpName = new QTableWidgetItem(QString::fromStdString(name));
    QTableWidgetItem *itemGrpSize = new QTableWidgetItem(QString::number(size));
    //QTableWidgetItem *itemGrpPeopleNames = new QTableWidgetItem()

    //Setting Item Placement
    tableWidget->setItem(itemRow, itemColumn, itemGrpName);
    tableWidget->setItem(itemRow, itemColumn + 1, itemGrpSize); //increment column
    //tableWidget->setItem(itemRow, itemColumn + 2, );
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



