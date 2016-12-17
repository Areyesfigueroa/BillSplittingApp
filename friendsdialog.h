#ifndef FRIENDSDIALOG_H
#define FRIENDSDIALOG_H

#include <QDialog>
#include <QVBoxLayout>
#include <QPushButton>
#include <QLineEdit>
#include "person.h"

namespace Ui {
class FriendsDialog;
}

class FriendsDialog : public QDialog
{
    Q_OBJECT

    static int sIndex;
public:
    explicit FriendsDialog(QWidget *parent = 0);
    ~FriendsDialog();


private slots:
    void on_confirmButton_clicked();
    void onAddFriends(int grpSize);

signals:
    void updateTableInfo();
private:
    Ui::FriendsDialog *ui;

    //Data
    QPushButton *confirmButton;
    QVBoxLayout *multLayouts;

    //Get user Input
    QLineEdit **nameTracker;
    QLineEdit **emailTracker;
    QLineEdit **phoneTracker;

    //functions
    QVBoxLayout* createUIAttributes();
    void deleteTrackers();
    void clearLayout(QLayout*, bool);
    void personInfo(std::string&, std::string&, std::string&);
};

#endif // FRIENDSDIALOG_H
