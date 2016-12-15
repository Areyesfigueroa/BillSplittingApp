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
private slots:
    void on_plusButton_clicked();
    void onGroupCreated();
    void onEditGroup(std::string, int);
    void onUpdateTableInfo();

    void on_editButton_clicked();

    void on_createBillButton_clicked();
    void onBillCreated(float);

private:
    //Windows
    Ui::MainWindow *ui;
    QTableWidget *tableWidget;
    CreateGroupDialog *createGrpDialog;
    EditGroupDialog *editGroupDialog;
    FriendsDialog *friendsDialog;
    BillOptionsDialog *billOptionsDialog;

    //Data
    static int tableRow;
    static int itemRow, itemColumn;

};

#endif // MAINWINDOW_H
