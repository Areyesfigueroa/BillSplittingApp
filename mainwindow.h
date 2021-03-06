#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "creategroupdialog.h"

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

private:
    Ui::MainWindow *ui;
    CreateGroupDialog *createGrpDialog;
};

#endif // MAINWINDOW_H
