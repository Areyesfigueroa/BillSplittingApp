#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "grouprecords.h"

//list lives here

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
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
        //This is where you connect it// FUCKING AWESOME
        connect(createGrpDialog, SIGNAL(updateList()), this, SLOT(onGroupCreated()));
    }
    createGrpDialog->show();
}

void MainWindow::onGroupCreated()
{
    //fetch the group from the groupRecords and
    //get its name to be displayed in the listWidget
    //testing

    GroupRecords *_instance = GroupRecords::instance(); //Helps keep the code shorter
    //QString groupName = QString::fromStdString(_instance->fetchLatestGroup()->getName());//convert Qstring to string
    //ui->listWidget->addItem(groupName); //testing
    _instance->setIndex(_instance->getIndex()+1); //increment index
}

void MainWindow::on_editButton_clicked()
{
    //Edit the group name and size
}
