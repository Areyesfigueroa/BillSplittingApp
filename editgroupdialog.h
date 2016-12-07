#ifndef EDITGROUPDIALOG_H
#define EDITGROUPDIALOG_H

#include <QDialog>
#include <QWidget>
#include "group.h"

namespace Ui {
class EditGroupDialog;
}

class EditGroupDialog : public QDialog
{
    Q_OBJECT

public:
    explicit EditGroupDialog(QWidget *parent = 0);
    ~EditGroupDialog();

signals:
    void groupChanged(std::string newGrpName, int newGrpSize);

private slots:
    void on_okButton_clicked();

private:
    Ui::EditGroupDialog *ui;
    Group *groupPtr;
};

#endif // EDITGROUPDIALOG_H
