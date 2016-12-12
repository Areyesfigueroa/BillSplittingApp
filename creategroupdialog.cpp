#include "creategroupdialog.h"
#include "ui_creategroupdialog.h"
#include "grouprecords.h"

CreateGroupDialog::CreateGroupDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CreateGroupDialog)
{
    ui->setupUi(this);
    ui->labelWarning->hide();

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

    //get userInput
    std::string grpName = ui->lineEditGroupName->text().toStdString();
    int grpSize = ui->lineEditGroupSize->text().toInt();

    //Check Duplicates
    if(GroupRecords::instance()->getRecords().checkForDuplicates(grpName))
    {
        //Display label
        ui->labelWarning->show();
        return;
    }
    else
    {
        //Allocates the new groups
        groupPtr = new Group(grpName, grpSize);

        //adding group ref
        GroupRecords::instance()->getRecords().addToRecords(groupPtr);

        //Clear the text boxes
        this->ui->lineEditGroupName->clear();//works
        this->ui->lineEditGroupSize->clear();//works

        //Close the Dialog window
        this->close();

        //hide warning label
        ui->labelWarning->hide();

        //Sending Signal
        this->updateList();
        this->addFriends(grpSize);

    }
}
