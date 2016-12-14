#include "billoptionsdialog.h"
#include "ui_billoptionsdialog.h"
#include "grouprecords.h"
#include "group.h"

BillOptionsDialog::BillOptionsDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::BillOptionsDialog)
{
    ui->setupUi(this);
}

BillOptionsDialog::~BillOptionsDialog()
{
    delete ui;
}

void BillOptionsDialog::updatingBillComboBoxes()
{
    //Get people on the combo box entered from the groupRecords
    //Display all the groups on the comboBox that you want to edit.

    //get the group records size
    int grpRecCount = GroupRecords::instance()->groupRecords.getSize();

    //Loop to get all the groupsName
    for(int i = 0; i < grpRecCount; i++)
    {
        //get the group
        Group* groups  = GroupRecords::instance()->groupRecords.fetchRecordsByIndex(i);

        //adding the group name onto the box
        ui->comboBoxGroupList->addItem(QString::fromStdString(groups->getGroupName()));
    }


    //People names from the group
    //ui->comboBoxPaidBy->addItem();

    billCreated();//signal update info on the mainWindow//May not have to
}

void BillOptionsDialog::comboBoxUpdate()
{
    //Get people on the combo box entered from the groupRecords
    //Display all the groups on the comboBox that you want to edit.

    //get the group records size
    int grpRecCount = GroupRecords::instance()->groupRecords.getSize();

    //Loop to get all the groupsName
    for(int i = 0; i < grpRecCount; i++)
    {
        //get the group
        Group* groups  = GroupRecords::instance()->groupRecords.fetchRecordsByIndex(i);

        //adding the group name onto the box
        ui->comboBoxGroupList->addItem(QString::fromStdString(groups->getGroupName()));
    }


    //People names from the group
    //ui->comboBoxPaidBy->addItem();

    billCreated();//signal update info on the mainWindow//May not have to
}

void BillOptionsDialog::on_confirmBillButton_clicked()
{

}
