#ifndef CREATEGROUPDIALOG_H
#define CREATEGROUPDIALOG_H

#include <QDialog>
#include <QWidget>

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

private:
    Ui::CreateGroupDialog *ui;

};

#endif // CREATEGROUPDIALOG_H
