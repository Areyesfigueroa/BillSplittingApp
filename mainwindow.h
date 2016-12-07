#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QListWidget>
#include "creategroupdialog.h"
#include "editgroupdialog.h"

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
    Ui::MainWindow *ui;
    CreateGroupDialog *createGrpDialog;
    EditGroupDialog *editGroupDialog;

};

#endif // MAINWINDOW_H
