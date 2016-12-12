#include "friendsdialog.h"
#include "ui_friendsdialog.h"
#include "person.h"
#include <QHBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include <QTextStream>
#include <QObject>
#include <string>
#include <QString>

//default
int FriendsDialog::sIndex = 0;

FriendsDialog::FriendsDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::FriendsDialog)
{
    multLayouts = 0;

    nameTracker = new QLineEdit*[sIndex]; //dynamic array//Delete after
    emailTracker = new QLineEdit*[sIndex];
    phoneTracker = new QLineEdit*[sIndex];

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

     int maxIndex = sIndex;
     sIndex = 0;
    //Passing info
    while(sIndex < maxIndex)
    {
    personInfo(nameTracker[sIndex]->text().toStdString(),
               phoneTracker[sIndex]->text().toStdString(),
               emailTracker[sIndex]->text().toStdString());
    sIndex++;
    }
    sIndex = 0;
    //Clear the trackers

    clearLayout(childLayout, true);
    delete childLayout;
    this->close();
}

void FriendsDialog::deleteTrackers()
{

}

void FriendsDialog::onAddFriends(int grpSize)
{
    QTextStream out(stdout);

    //Multiple Layouts
    multLayouts = new QVBoxLayout();
    std::string multName = multLayouts->layout()->objectName().toStdString();
    out << multName.c_str()<<endl;

    while(sIndex < grpSize)
    {
        multLayouts->addLayout(createUIAttributes());
        sIndex++;
    }
    std::string name = confirmButton->text().toStdString();
    out << name.c_str() <<endl;
    multLayouts->addWidget(confirmButton); //it is getting destroyed
    this->setLayout(multLayouts);
}

void FriendsDialog::clearLayout(QLayout* layout, bool deleteWidgets = true)
{
    QTextStream out(stdout);

    while(QLayoutItem *item = layout->takeAt(0))
    {
        QWidget *widget;
        if((deleteWidgets) &&(widget = item->widget()))
        {
            //stop deleting the button
            if(widget == confirmButton)
            {
                out << "Equal"<<endl;
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

    //trackers
    nameTracker[sIndex] = lineEditName;
    phoneTracker[sIndex] = lineEditPhoneNum;
    emailTracker[sIndex] = lineEditEmail;

    return verticalLayout;
}

void FriendsDialog::personInfo( std::string& name,  std::string& phoneNum, std::string& email)
{
    Person *person = new Person(name, phoneNum, email);
}
