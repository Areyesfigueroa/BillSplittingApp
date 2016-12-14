#include "billoptionsdialog.h"
#include "ui_billoptionsdialog.h"

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
