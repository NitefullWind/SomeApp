#ifndef USERPWD_H
#define USERPWD_H
#include <QDialog>

namespace Ui {
class userPwd;
}

class userPwd : public QDialog
{
    Q_OBJECT

public:
    userPwd(QWidget *parent = 0, QString name=NULL);
    ~userPwd();

private slots:
    void on_pushButton_clicked();

    void on_inputPwd_textChanged(const QString &arg1);

    void on_againPwd_textChanged(const QString &arg1);

private:
    Ui::userPwd *ui;
    QString *userNameTxt;
    QString *pwdTxt;
};

#endif // USERPWD_H
