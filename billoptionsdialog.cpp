#include "billoptionsdialog.h"
#include "ui_billoptionsdialog.h"
#include "grouprecords.h"
#include "group.h"
#include <QMessageBox>

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

void BillOptionsDialog::comboBoxUpdate()
{
    if(!GroupRecords::instance()->groupRecords.isEmpty())
    {
        insertGroupToComboBox();
        billCreated();//signal update info on the mainWindow//May not have to
    }
    else
    {
        return;
    }
}

void BillOptionsDialog::insertGroupToComboBox()
{
    //get the group records size
    size_t grpRecCount = GroupRecords::instance()->groupRecords.getSize();

    Group* groups = 0;
    //Loop to get all the groupsName
    for(int i = 0; i < grpRecCount; i++)
    {
        //get the group
        groups  = GroupRecords::instance()->groupRecords.fetchRecordsByIndex(i);

        //adding the group name onto the box
        ui->comboBoxGroupList->addItem(QString::fromStdString(groups->getGroupName()));
    }
}

//this depends on the group selected, Will work Once for now
void BillOptionsDialog::insertPersonToComboBox()
{
}

void BillOptionsDialog::on_confirmBillButton_clicked()
{
    ui->comboBoxPaidBy->clear();

    ui->comboBoxGroupList->clear();
    //ui->comboBoxSplitOptions->clear();

    this->close();
}

//activates when you change the index
void BillOptionsDialog::on_comboBoxGroupList_currentIndexChanged(int index)
{
    if(index == -1)
    {
        return;
    }
    else
    {
        if(GroupRecords::instance()->groupRecords.isEmpty())
        {
            return;
        }
        else
        {
            //use the index to fetchgroupByindex
            Group* currentGrp = GroupRecords::instance()->groupRecords.fetchRecordsByIndex(index);

            //size of people
            size_t size = currentGrp->getPeopleCount();

            for(int i = 0; i < size; i++)
            {
                ui->comboBoxPaidBy->addItem(QString::fromStdString(currentGrp->getPersonByIndex(i)->getPersonName()));
            }
        }
    }
}
