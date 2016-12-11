#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QListWidget>
#include <QTableWidget>
#include "creategroupdialog.h"
#include "editgroupdialog.h"
#include "friendsdialog.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();


private slots:
    void on_plusButton_clicked();
    void onGroupCreated();
    void onEditGroup(std::string, int);

    void on_editButton_clicked();

private:
    //Windows
    Ui::MainWindow *ui;
    QTableWidget *tableWidget;
    CreateGroupDialog *createGrpDialog;
    EditGroupDialog *editGroupDialog;
    FriendsDialog *friendsDialog;

    //Data
    static int tableRow;
    static int itemRow, itemColumn;

    //Functions
    void updateTable(const std::string&, int&);
    void createFriendsDialogConnection();

};

#endif // MAINWINDOW_H
