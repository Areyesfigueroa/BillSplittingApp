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

    void comboBoxUpdate();


signals:
    void createBillClicked();
    void billCreated();

private slots:
    void on_confirmBillButton_clicked();
    void updatingBillComboBoxes(); //before opening window

private:
    Ui::BillOptionsDialog *ui;

};

#endif // BILLOPTIONSDIALOG_H
