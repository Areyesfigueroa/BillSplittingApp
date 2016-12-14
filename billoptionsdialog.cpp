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
        insertSplitOptionsToComboBox();
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

void BillOptionsDialog::on_confirmBillButton_clicked()
{
    ui->comboBoxPaidBy->clear();
    ui->comboBoxGroupList->clear();
    ui->comboBoxSplitOptions->clear();

    this->close();
}

//activates when you change the index
void BillOptionsDialog::on_comboBoxGroupList_currentIndexChanged(int index)
{
    ui->comboBoxPaidBy->clear();
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

void BillOptionsDialog::insertSplitOptionsToComboBox()
{
    ui->comboBoxSplitOptions->addItem("Equally");
    ui->comboBoxSplitOptions->addItem("Individually");
    ui->comboBoxSplitOptions->addItem("They owe full ammount");
    ui->comboBoxSplitOptions->addItem("You owe full ammount");
}

void BillOptionsDialog::on_comboBoxSplitOptions_currentIndexChanged(int index)
{
    //Changes depending on how you want to split your bills
    if(index == 0) //Equal
    {

    }
}

void BillOptionsDialog::on_lineEditTotalBill_textEdited(const QString &arg1)
{
    int total = arg1.toInt();
}
