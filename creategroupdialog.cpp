#include "creategroupdialog.h"
#include "ui_creategroupdialog.h"
#include "group.h"
#include "grouprecords.h"

CreateGroupDialog::CreateGroupDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CreateGroupDialog)
{
    ui->setupUi(this);
}

CreateGroupDialog::~CreateGroupDialog()
{
    delete ui;
}

void CreateGroupDialog::on_createButton_clicked()
{
    //Adds the user input into my group
    //creates a new instance everytime
    Group *groupPtr = new Group(ui->lineEditGroupName->text().toStdString(),
                             ui->lineEditGroupSize->text().toInt());

    GroupRecords::instance()->addGroup(groupPtr); //adding group pointer
    emit this->updateList();//sending the signal
}
