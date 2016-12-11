#ifndef FRIENDSDIALOG_H
#define FRIENDSDIALOG_H

#include <QDialog>

namespace Ui {
class FriendsDialog;
}

class FriendsDialog : public QDialog
{
    Q_OBJECT

public:
    explicit FriendsDialog(QWidget *parent = 0);
    ~FriendsDialog();

private slots:
    void onAddFriends();

private:
    Ui::FriendsDialog *ui;
};

#endif // FRIENDSDIALOG_H
