#include "creategroupdialog.h"
#include "ui_creategroupdialog.h"
#include "group.h"

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
    Group *groupPtr = new Group(ui->lineEditGroupName->text().toStdString(),
                             ui->lineEditGroupSize->text().toInt()); //creates a new instance everytime
    //After adding the group Data in, place the groupPtr in the groupRecorder for editing
    emit this->updateList();
}
