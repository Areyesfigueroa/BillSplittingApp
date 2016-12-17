#include "billoptionsdialog.h"
#include "ui_billoptionsdialog.h"
#include "grouprecords.h"
#include <algorithm>
#include <QMessageBox>

BillOptionsDialog::BillOptionsDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::BillOptionsDialog)
{

    //dynamic double pointer arrays, init
    horBoxLayout = new QHBoxLayout*[0];
    lineEditBillAmmount = new QLineEdit*[0];
    labelPersonName = new QLabel*[0];

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

    //Loop to get all the groupsName
    for(int i = 0; i < grpRecCount; i++)
    {
        //get the group
        Group* groups  = getGroupByIndex(i);

        //adding the group name onto the box
        ui->comboBoxGroupList->addItem(QString::fromStdString(groups->getGroupName()));
    }
}

//Activates when you press the confirm button
void BillOptionsDialog::on_confirmBillButton_clicked()
{
    addIndividualBills();

    ui->comboBoxPaidBy->clear();
    ui->comboBoxGroupList->clear();
    ui->comboBoxSplitOptions->clear();

    //saves the total bill for now
    billCreated(ui->lineEditTotalBill->text().toFloat()); //goes back to main

    this->close();
}

void BillOptionsDialog::addIndividualBills()
{
    //use the index to fetchgroupByindex
    Group* currentGrp = getGroupByIndex(ui->comboBoxGroupList->currentIndex());

    //size of people
    size_t size = currentGrp->getPeopleCount();

    for(int i = 0; i < size; i++)
    {
        float bill = lineEditBillAmmount[i]->text().toFloat();
        currentGrp->getPersonByIndex(i)->addToBillRecords(currentGrp->getGroupName(), bill); //this is how much you owe
    }
}

//activates when you change the index of the group
void BillOptionsDialog::on_comboBoxGroupList_currentIndexChanged(int index)
{
    ui->comboBoxPaidBy->clear();
    if(index == -1) //index turns to negative one when closing or opening this window
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

            //Adding people to combo box
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
    //FUTURE IMPLEMENTATION
    //ui->comboBoxSplitOptions->addItem("They owe full ammount"); //2
    //ui->comboBoxSplitOptions->addItem("You owe full ammount"); //3
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
    Group* grp = getGroupByIndex(grpIndex);

    for(int i = 0; i < grp->getPeopleCount(); i++)
    {
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
    total = total - ui->lineEditTotalBill->text().toFloat(); //NOT IMPLEMENTED Future: print on screen
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
        createWindows(index, getEqualAmmount(), false);
    }
    else if(ui->comboBoxSplitOptions->currentIndex() == 1)
    {
        createWindows(index, getEqualAmmount(), true);
        addIndividualSetting();
    }
}
