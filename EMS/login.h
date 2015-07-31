#ifndef LOGIN_H
#define LOGIN_H

#include <QDialog>

namespace Ui {
class Login;
}

class Login : public QDialog
{
    Q_OBJECT

public:
    explicit Login(QWidget *parent = 0);
    QString getUserName();
    QString getUserGrade();
    ~Login();

private slots:
    void on_loginButton_clicked();

    void on_cancelButton_clicked();


private:
    Ui::Login *ui;
    QString name, pwd, grade;
};

#endif // LOGIN_H
