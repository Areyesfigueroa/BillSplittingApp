#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QListWidget>
#include <QTableWidget>
#include <functional>
#include "creategroupdialog.h"
#include "editgroupdialog.h"
#include "friendsdialog.h"
#include "billoptionsdialog.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    void createFriendsDialogConnection();
    void updateTable();
    void updateBill(std::function<int()>);

    //Destructor functions
    void deleteBillDataTable();//store first, when db is included
    void deleteGroupDataTable();

private slots:
    void on_plusButton_clicked();
    void onGroupCreated();
    void onEditGroup(std::string, int);
    void onUpdateTableInfo();

    void on_editButton_clicked();

    void on_createBillButton_clicked();
    void onBillCreated(float);
    void updatePeopleOnBPTable();
    void updateBillOnBPTable();


private:
    //Windows
    Ui::MainWindow *ui;
    QTableWidget *tableWidget;
    QTableWidget *paymentTableWidget;
    CreateGroupDialog *createGrpDialog;
    EditGroupDialog *editGroupDialog;
    FriendsDialog *friendsDialog;
    BillOptionsDialog *billOptionsDialog;

    //Group Table Data
    static int tableRow;
    static int itemRow, itemColumn;

    //Payment Table Data
    static int paymentTableRow;
    static int paymentItemRow, paymentItemColumn;

    //FriendsTable Data
    QTableWidgetItem **itemPersonName;
    QTableWidgetItem **itemGrpName;
    QTableWidgetItem **itemBill;
    QTableWidgetItem **itemBillPayed;
};

#endif // MAINWINDOW_H
