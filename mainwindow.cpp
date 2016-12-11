#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "grouprecords.h"
#include <QTextStream>

//list lives here
//Check with teacher to choose the most optimal way of checking for duplicates
//For now do not enter duplicate groups.
//Check using a find

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    //init
    createGrpDialog = 0;
    editGroupDialog = 0;
    ui->setupUi(this);
    tableWidget = ui->tableWidget;
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_plusButton_clicked()
{
    if(!createGrpDialog)//Creates one instance at a time
    {
        //To use the second window create an instance of the class
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
//connected
void MainWindow::onGroupCreated()
{
    //getting instance
    GroupRecords *_instance = GroupRecords::instance(); //Helps keep the code shorter

    //getting latest groupName
    std::string grpName = _instance->fetchLatestGroup()->getName();
    int grpSize = _instance->fetchLatestGroup()->getSize();

    //Adding name to listWidget
    ui->listWidget->addItem(QString::fromStdString(grpName));

    //Setting Table Rows and Columns
    tableWidget->setRowCount(10);
    tableWidget->setColumnCount(4);

    //Changing Header
    tableWidget->setHorizontalHeaderLabels(QStringList()<<"Group Name"<<"Group Size"<< "People" << "Bills");

    //Row and Column for item placement
    int row, column;
    row = column = 0;

    //Items need to be newed, new Items
    QTableWidgetItem *itemGrpName = new QTableWidgetItem(QString::fromStdString(grpName));
    QTableWidgetItem *itemGrpSize = new QTableWidgetItem(QString::number(grpSize));

    //Setting Item Placement
    tableWidget->setItem(row, column, itemGrpName);
    tableWidget->setItem(row, column+1, itemGrpSize);

}

//connected
void MainWindow::onEditGroup(std::string newGrpName, int newGrpSize)
{
    int index = ui->listWidget->currentRow();
    QTextStream out(stdout);
    out << index;
    Group* currGroup = GroupRecords::instance()->fetchGroupByIndex(index);

    //overwrite the Group
    currGroup->setName(newGrpName);
    currGroup->setSize(newGrpSize);
    ui->listWidget->currentItem()->setText(QString::fromStdString(currGroup->getName()));
}


