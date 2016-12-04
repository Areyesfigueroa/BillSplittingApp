#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "grouprecords.h"

//list lives here
//Check with teacher to choose the most optimal way of checking for duplicates
//For now do not enter duplicate groups.

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
    //fetch the group from the groupRecords and
    //get its name to be displayed in the listWidget
    //testing
    GroupRecords *_instance = GroupRecords::instance(); //Helps keep the code shorter

    std::string testing = _instance->fetchLatestGroup()->getName();


    ui->listWidget->addItem(QString::fromStdString(testing));
    //Check for a way to stop duplicates
}

void MainWindow::on_editButton_clicked()
{
    //Edit the group name and size
    //get the current selecte item
    QListWidgetItem *item = ui->listWidget->currentItem();
    item->setTextColor(Qt::red);

}
