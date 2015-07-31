#ifndef USERLIMIT_H
#define USERLIMIT_H

#include <QDialog>

namespace Ui {
class UserLimit;
}

class UserLimit : public QDialog
{
    Q_OBJECT

public:
    explicit UserLimit(QWidget *parent = 0);
    ~UserLimit();

private slots:
    void on_addUserBtn_clicked();
    void on_yesBtn_clicked();

private:
    Ui::UserLimit *ui;
};

#endif // USERLIMIT_H
