#include "friendsdialog.h"
#include "ui_friendsdialog.h"

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
