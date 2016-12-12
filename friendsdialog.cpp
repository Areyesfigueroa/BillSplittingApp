#include "friendsdialog.h"
#include "ui_friendsdialog.h"
#include "person.h"
#include "peoplerecords.h"
#include <QHBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include <QTextStream>
#include <QObject>
#include <string>
#include <QString>

FriendsDialog::FriendsDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::FriendsDialog)
{
    multLayouts = 0;
    ui->setupUi(this);

    confirmButton = new QPushButton("Confirm", this);
    connect(confirmButton, SIGNAL(clicked()), this, SLOT(on_confirmButton_clicked()));
}

FriendsDialog::~FriendsDialog()
{
    delete ui;
}

void FriendsDialog::on_confirmButton_clicked()
{
    QLayout* childLayout = multLayouts->layout();

    //Passing info
   personInfo(tracker[0]->text().toStdString(),
               tracker[0]->text().toStdString(),
               tracker[0]->text().toStdString());

    sendingPersonInfo(childLayout, true);
    clearLayout(childLayout, true);
    delete childLayout;
    this->close();
}

void FriendsDialog::onAddFriends(int grpSize)
{
    QTextStream out(stdout);

    //Multiple Layouts
    multLayouts = new QVBoxLayout();

    int index = 0;
    while(index < grpSize)
    {
        multLayouts->addLayout(createUIAttributes());



        index++;
    }
    Records<Person*> *rec = &personContainer;

    multLayouts->addWidget(confirmButton); //it is getting destroyed
    this->setLayout(multLayouts);
}

void FriendsDialog::clearLayout(QLayout* layout, bool deleteWidgets = true)
{
    while(QLayoutItem *item = layout->takeAt(0))
    {
        QWidget *widget;
        if((deleteWidgets) &&(widget = item->widget()))
        {
            //stop deleting the button
            if(widget == confirmButton)
            {
                return;
            }
            else
            {
                delete widget;
            }
        }
        if(QLayout* childLayout = item->layout())
        {
            clearLayout(childLayout, deleteWidgets);
        }
        delete item;
    }
}

void FriendsDialog::sendingPersonInfo(QLayout* layout, bool deleteWidgets = true)
{
    QObjectList objList = layout->children();
    QVBoxLayout* vertLayout;
    QObject* obj = objList.back();
}

QVBoxLayout* FriendsDialog::createUIAttributes()
{
    //create Layouts
    QVBoxLayout *verticalLayout = new QVBoxLayout();
    QHBoxLayout *horLayoutName = new QHBoxLayout();
    QHBoxLayout *horLayoutPhoneNum = new QHBoxLayout();
    QHBoxLayout *horLayoutEmail = new QHBoxLayout();

    //Create label
    QLabel *labelTitle = new QLabel("Friend Information: ");
    QLabel *labelName = new QLabel("Name: ");
    QLabel *labelPhoneNum = new QLabel("Phone#: ");
    QLabel *labelEmail = new QLabel("Email: ");

    //tracker
   // tracker[0] = labelTitl;
    //Create lineEdit
    QLineEdit *lineEditName = new QLineEdit();
    QLineEdit *lineEditPhoneNum = new QLineEdit();
    QLineEdit *lineEditEmail = new QLineEdit();

    //Assemble layout
    //Name
    horLayoutName->addWidget(labelName);
    horLayoutName->addWidget(lineEditName);
    //Phone
    horLayoutPhoneNum->addWidget(labelPhoneNum);
    horLayoutPhoneNum->addWidget(lineEditPhoneNum);
    //Email
    horLayoutEmail->addWidget(labelEmail);
    horLayoutEmail->addWidget(lineEditEmail);

    //Add to vertical layout
    verticalLayout->addWidget(labelTitle);
    verticalLayout->addLayout(horLayoutName);
    verticalLayout->addLayout(horLayoutPhoneNum);
    verticalLayout->addLayout(horLayoutEmail);


    //Store LineEdits
    tracker[0] = lineEditName;
    return verticalLayout;
}

void FriendsDialog::personInfo( std::string& name,  std::string& phoneNum, std::string& email)
{
    //Loops many times
    Person *person = new Person(name, phoneNum, email);

    //add to person records
    personContainer.addToRecords(person);
}
