#ifndef BILLOPTIONSDIALOG_H
#define BILLOPTIONSDIALOG_H

#include <QDialog>
#include "group.h"

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
    void insertGroupToComboBox();
    void insertSplitOptionsToComboBox();

signals:
    void createBillClicked();
    void billCreated();

private slots:
    void on_confirmBillButton_clicked();

    void on_comboBoxGroupList_currentIndexChanged(int index);

    void on_comboBoxSplitOptions_currentIndexChanged(int index);

    void on_lineEditTotalBill_textEdited(const QString &arg1);

private:
    Ui::BillOptionsDialog *ui;

    Group* tempGrp;
};

#endif // BILLOPTIONSDIALOG_H
