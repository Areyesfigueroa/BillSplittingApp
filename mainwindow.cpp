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
    //fetch the group from the groupRecords and
    //get its name to be displayed in the listWidget
    //testing
    GroupRecords *_instance = GroupRecords::instance(); //Helps keep the code shorter

    std::string testing = _instance->fetchLatestGroup()->getName();
    //original
    ui->listWidget->addItem(QString::fromStdString(testing));
    //Check for a way to stop duplicates
    //Disconnect the signal
    //disconnect(createGrpDialog, SIGNAL(updateList()), this, SLOT(onGroupCreated()));

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


