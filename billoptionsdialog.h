#ifndef BILLOPTIONSDIALOG_H
#define BILLOPTIONSDIALOG_H

#include <QDialog>

namespace Ui {
class BillOptionsDialog;
}

class BillOptionsDialog : public QDialog
{
    Q_OBJECT

public:
    explicit BillOptionsDialog(QWidget *parent = 0);
    ~BillOptionsDialog();

signals:
    void createBillClicked();

private:
    Ui::BillOptionsDialog *ui;
};

#endif // BILLOPTIONSDIALOG_H
