#ifndef LOGINDIALOG_H
#define LOGINDIALOG_H

#include <QDialog>

namespace Ui {
class LoginDialog;
}

class LoginDialog : public QDialog
{
    Q_OBJECT

public:
    explicit LoginDialog(QWidget *parent = 0);
    ~LoginDialog();
    QString getUsetName() {return name;}

private slots:
    void on_loginBtn_clicked();

    void on_quitBtn_clicked();

    void on_signUpBtn_clicked();

private:
    Ui::LoginDialog *ui;
    bool checkNull();
    QString name,pwd;
};

#endif // LOGINDIALOG_H
