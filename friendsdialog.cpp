#include "friendsdialog.h"
#include "ui_friendsdialog.h"
#include <QHBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>

FriendsDialog::FriendsDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::FriendsDialog)
{
    ui->setupUi(this);
}

FriendsDialog::~FriendsDialog()
{
    delete ui;
}

void FriendsDialog::onAddFriends(int grpSize)
{
    //Multiple Layouts
    QVBoxLayout *multLayouts = new QVBoxLayout();
    int index = 0;
    while(index < grpSize)
    {
        multLayouts->addLayout(createUIAttributes());
        index++;
    }
    this->setLayout(multLayouts);
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


    //Create confirm button
    QPushButton *confirmButton = new QPushButton("Confirm");

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
    verticalLayout->addWidget(confirmButton);

    return verticalLayout;
}
