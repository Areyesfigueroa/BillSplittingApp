#include "mainwindow.h"
#include "ui_mainwindow.h"

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
    //This is where you connect it
    connect(createGrpDialog, SIGNAL(updateList()), this, SLOT(onGroupCreated()));
    }
    createGrpDialog->show();
}

void MainWindow::onGroupCreated()
{
    //add the groupRecords to the list
    //testing
    ui->listWidget->addItem("Group 1 created");
}
