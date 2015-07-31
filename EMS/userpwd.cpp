#include "userpwd.h"
#include "ui_userpwd.h"
#include <QMessageBox>
#include "core/tableusers.h"

userPwd::userPwd(QWidget *parent, QString name) :
    QDialog(parent),
    ui(new Ui::userPwd)
{
    ui->setupUi(this);
    ui->inputUserName->setText(name);
    userNameTxt = new QString[1];
    pwdTxt = new QString[2];

    QPalette palette;
        palette.setBrush(QPalette::Background, QBrush(QPixmap("d:/Xiaoxueqi/320-240.png")));
        this->setPalette(palette);
}

userPwd::~userPwd()
{
    delete ui;
}

void userPwd::on_pushButton_clicked()
{

    TableUsers u;
    if(pwdTxt[0]==pwdTxt[1]&&pwdTxt[0]!=NULL)
    {
    //    u.updateRecord(u.getUserPwd())=pwdTxt[1];
        u.setUserPwd(ui->inputUserName->text(),pwdTxt[0]);
        QMessageBox::information(NULL,"Warning","密码修改成功！",QMessageBox::Ok);
        this->close();
    }
    else
    {
        QMessageBox::information(NULL,"Warning","两次输入密码不同，请重新输入！",QMessageBox::Ok);
    }
}

void userPwd::on_inputPwd_textChanged(const QString &arg2)
{
    pwdTxt[0]=arg2;
}

void userPwd::on_againPwd_textChanged(const QString &arg3)
{
    pwdTxt[1]=arg3;
}
