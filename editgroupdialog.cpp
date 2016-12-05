#include "editgroupdialog.h"
#include "ui_editgroupdialog.h"

EditGroupDialog::EditGroupDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::EditGroupDialog)
{
    ui->setupUi(this);
}

EditGroupDialog::~EditGroupDialog()
{
    delete ui;
}

void EditGroupDialog::on_pushButton_clicked()
{
    //Need to check that the group is not empty text

    //Check if input is null
    if(ui->lineEditGrpName->text().isEmpty())
    {
        return;
    }

    //Clear the text boxes
    this->ui->lineEditGrpName->clear();//works
    this->ui->lineEditGrpSize->clear();//works

    //Close the Dialog window
    this->close();

    //Sending Signal
    emit this->groupChanged();
}
