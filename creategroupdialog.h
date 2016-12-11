#ifndef CREATEGROUPDIALOG_H
#define CREATEGROUPDIALOG_H

#include <QDialog>
#include <QWidget>
#include "group.h"

namespace Ui {
class CreateGroupDialog;
}

class CreateGroupDialog : public QDialog
{
    Q_OBJECT

public:
    explicit CreateGroupDialog(QWidget *parent = 0);
    ~CreateGroupDialog();

private slots:
    void on_createButton_clicked();

signals:
    void updateList();
    void addFriends(int);

private:
    Ui::CreateGroupDialog *ui;
    Group *groupPtr;
};

#endif // CREATEGROUPDIALOG_H
