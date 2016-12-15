#include "billoptionsdialog.h"
#include "ui_billoptionsdialog.h"
#include "grouprecords.h"
#include "group.h"
#include <QMessageBox>

BillOptionsDialog::BillOptionsDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::BillOptionsDialog)
{

    //dynamic double pointer arrays
    horBoxLayout = new QHBoxLayout*[0];
    lineEditBillAmmount = new QLineEdit*[0];
    labelPersonName = new QLabel*[0]; //label points to new QLabel, Qlabel points to array

    ui->setupUi(this);
}

BillOptionsDialog::~BillOptionsDialog()
{
    deleteWindows();
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

//Activates when you press the confirm button
void BillOptionsDialog::on_confirmBillButton_clicked()
{
    ui->comboBoxPaidBy->clear();
    ui->comboBoxGroupList->clear();
    ui->comboBoxSplitOptions->clear();

    //deleteWindows();

    this->close();
}

//activates when you change the index of the group
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

            reset();
        }
    }
}

void BillOptionsDialog::reset()
{
    ui->lineEditTotalBill->clear();
    deleteWindows();
}

void BillOptionsDialog::insertSplitOptionsToComboBox()
{
    ui->comboBoxSplitOptions->addItem("Equally"); //0
    ui->comboBoxSplitOptions->addItem("Individually"); //1
   // ui->comboBoxSplitOptions->addItem("They owe full ammount"); //2
   // ui->comboBoxSplitOptions->addItem("You owe full ammount"); //3
}

void BillOptionsDialog::on_comboBoxSplitOptions_currentIndexChanged(int index)
{
    //Changes depending on how you want to split your bills
    switch(index)
    {
    case(0):
        addEqualSetting();
        break;
    case(1):
        addIndividualSetting();
        break;
    default:
        break;
    }
}
void BillOptionsDialog::addEqualSetting()
{
    //Adds groups peoples bills evenly

    int index = ui->comboBoxGroupList->currentIndex();
    Group* group = GroupRecords::instance()->groupRecords.fetchRecordsByIndex(index);
    evenAmmount = (ui->lineEditTotalBill->text().toFloat()) / static_cast<float>(group->getPeopleCount());
    //display the data to the user
}

int BillOptionsDialog::getEqualAmmount() const
{
    return evenAmmount;
}

void BillOptionsDialog::createWindows(int index, float billAmmount)
{

    //create windows for people to see their bills


    Group* grp = GroupRecords::instance()->groupRecords.fetchRecordsByIndex(index);

    for(int i = 0; i < grp->getPeopleCount(); i++)
    {
        //Make sure to delete
        horBoxLayout[i] = new QHBoxLayout();
        labelPersonName[i] = new QLabel(QString::fromStdString(grp->getPersonByIndex(i)->getPersonName()));
        lineEditBillAmmount[i] = new QLineEdit(QString::number(billAmmount));
        lineEditBillAmmount[i]->setReadOnly(true);

        horBoxLayout[i]->addWidget(labelPersonName[i]);
        horBoxLayout[i]->addWidget(lineEditBillAmmount[i]);

        ui->vertBaseLayout->addLayout(horBoxLayout[i]);
    }

}

void BillOptionsDialog::deleteWindows()
{
    int counter = 0;
    while(!ui->vertBaseLayout->isEmpty())
    {
        delete[] labelPersonName[counter];
        delete[] lineEditBillAmmount[counter];
        delete[] horBoxLayout[counter];
        counter++;
    }

}

void BillOptionsDialog::addIndividualSetting()
{
    //get all people records from this group
    //create multiple line edits so that you can you can input their ammounts individually
    //create trackers for the line edits do that you can track the information
    //formula: add all the individual ammounts - the total ammount input it.
}

void BillOptionsDialog::on_lineEditTotalBill_editingFinished()
{
    //Whenever you change the total
    if(!ui->vertBaseLayout->isEmpty())
    {
        deleteWindows();
    }
    addEqualSetting();
    int index = ui->comboBoxGroupList->currentIndex();
    createWindows(index, getEqualAmmount());
}
