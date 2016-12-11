#ifndef FRIENDSDIALOG_H
#define FRIENDSDIALOG_H

#include <QDialog>
#include <QVBoxLayout>


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
    void onAddFriends(int grpSize);

private:
    Ui::FriendsDialog *ui;


    //functions
    QVBoxLayout* createUIAttributes();
};

#endif // FRIENDSDIALOG_H
