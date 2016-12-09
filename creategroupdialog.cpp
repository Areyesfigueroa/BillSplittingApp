#include "creategroupdialog.h"
#include "ui_creategroupdialog.h"
#include "grouprecords.h"

CreateGroupDialog::CreateGroupDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CreateGroupDialog)
{
    ui->setupUi(this);
}

CreateGroupDialog::~CreateGroupDialog()
{
    delete ui; //will delete all pointers with it
}

void CreateGroupDialog::on_createButton_clicked()
{
    //Need to check that the group is not empty text

    //Check if input is null
    if(ui->lineEditGroupName->text().isEmpty())
    {
        return;
    }

    groupPtr = new Group(ui->lineEditGroupName->text().toStdString(),
                             ui->lineEditGroupSize->text().toInt());
    //Adds the user input into my group
    //creates a new instance everytime

    //adding group pointer
    GroupRecords::instance()->addGroup(groupPtr);

    //Clear the text boxes
    this->ui->lineEditGroupName->clear();//works
    this->ui->lineEditGroupSize->clear();//works

    //Close the Dialog window
    this->close();

    //Sending Signal
    this->updateList();
}
