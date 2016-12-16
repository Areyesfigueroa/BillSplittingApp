#ifndef BILLOPTIONSDIALOG_H
#define BILLOPTIONSDIALOG_H

#include <QDialog>
#include <QHBoxLayout>
#include <QLineEdit>
#include <QLabel>

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

    void addEqualSetting();
    int getEqualAmmount() const;
    void addIndividualSetting();
    void owedYouFullAmmount();
    void youOweFullAmmount();
    void createWindows(int, float, bool);
    void deleteWindows();

    void reset();
    void addIndividualBills();

signals:
    void createBillClicked();
    void billCreated(float);

private slots:
    void on_confirmBillButton_clicked();

    void on_comboBoxGroupList_currentIndexChanged(int index);

    void on_comboBoxSplitOptions_currentIndexChanged(int index);

    void on_lineEditTotalBill_editingFinished();

private:
    Ui::BillOptionsDialog *ui;

    Group* tempGrp;

    //Windows Creation
    QHBoxLayout** horBoxLayout;
    QLineEdit** lineEditBillAmmount;
    QLabel** labelPersonName;

    //data
    float evenAmmount;
};

#endif // BILLOPTIONSDIALOG_H
