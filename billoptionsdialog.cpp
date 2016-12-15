#include "billoptionsdialog.h"
#include "ui_billoptionsdialog.h"
#include "grouprecords.h"
#include "group.h"
#include <algorithm>
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

//Lambda, more convinient
auto getGroupByIndex = [](int index)->Group*{ return GroupRecords::instance()->groupRecords.fetchRecordsByIndex(index);};
auto getPersonNameByIndex = [](Group* group, int index)->std::string{return group->getPersonByIndex(index)->getPersonName();};

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
        groups  = getGroupByIndex(i);

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

    //just save the total bill for now
    billCreated(ui->lineEditTotalBill->text().toFloat()); //goes back to main
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
            Group* currentGrp = getGroupByIndex(ui->comboBoxGroupList->currentIndex());

            //size of people
            size_t size = currentGrp->getPeopleCount();

            for(int i = 0; i < size; i++)
            {
                ui->comboBoxPaidBy->addItem(QString::fromStdString(getPersonNameByIndex(currentGrp, i)));
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
    Group* group = getGroupByIndex(index);
    evenAmmount = (ui->lineEditTotalBill->text().toFloat()) / static_cast<float>(group->getPeopleCount());
    //display the data to the user
}

int BillOptionsDialog::getEqualAmmount() const
{
    return evenAmmount;
}

void BillOptionsDialog::createWindows(int grpIndex, float billAmmount, bool isEditable = false)
{
    //create windows for people to see their bills
    Group* grp = getGroupByIndex(grpIndex);

    for(int i = 0; i < grp->getPeopleCount(); i++)
    {
        //Make sure to delete
        horBoxLayout[i] = new QHBoxLayout();
        labelPersonName[i] = new QLabel(QString::fromStdString(getPersonNameByIndex(grp, i)));
        lineEditBillAmmount[i] = new QLineEdit(QString::number(billAmmount));
        lineEditBillAmmount[i]->setReadOnly(isEditable);

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

    //get the current groupIndex
    int index = ui->comboBoxGroupList->currentIndex();
    Group* group = getGroupByIndex(index);

    int counter = 0;
    float total = 0;
    while(counter > group->getPeopleCount())
    {
        total +=lineEditBillAmmount[counter]->text().toFloat();
        counter++;
    }
    total = total - ui->lineEditTotalBill->text().toFloat(); //print on screen

    //update label
}

void BillOptionsDialog::on_lineEditTotalBill_editingFinished()
{
    int index = ui->comboBoxGroupList->currentIndex();
    //Whenever you change the total
    if(!ui->vertBaseLayout->isEmpty())
    {
        deleteWindows();
    }
    if(ui->comboBoxSplitOptions->currentIndex() == 0)
    {
        addEqualSetting();
        createWindows(index, getEqualAmmount());
    }
    else if(ui->comboBoxSplitOptions->currentIndex() == 1)
    {
        createWindows(index, getEqualAmmount(), true);
        addIndividualSetting();
    }
}
