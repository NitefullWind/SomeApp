#include "logindialog.h"
#include "ui_logindialog.h"
#include "connection.h"
#include <QDebug>

LoginDialog::LoginDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::LoginDialog)
{
    ui->setupUi(this);
    ui->loginBtn->setDefault(true);
}

LoginDialog::~LoginDialog()
{
    delete ui;
}

void LoginDialog::on_loginBtn_clicked()
{
    if(checkNull()){
        QMessageBox::information(this,"错误","请输入用户名和密码后再登录！",QMessageBox::Ok);
        ui->userNameEdit->setFocus();
    }else{
        QSqlQuery query;
        query.exec(QString("select upwd from tbl_users where uname='%1'").arg(name));
        if(query.next()){
            if(pwd==query.value(0).toString())
                QDialog::accept();
            else{
                QMessageBox::information(this,"错误","用户密码错误，请重新输入",QMessageBox::Ok);
                ui->userPwdEdit->clear();
                ui->userPwdEdit->setFocus();
            }
        }else{
            QMessageBox::information(this,"错误","未发现该用户，请重新输入或注册",QMessageBox::Ok);
            ui->userNameEdit->clear();
            ui->userPwdEdit->clear();
            ui->userNameEdit->setFocus();
        }
    }
}

void LoginDialog::on_quitBtn_clicked()
{
    QDialog::reject();
}

void LoginDialog::on_signUpBtn_clicked()
{
    if(checkNull()){
        QMessageBox::information(this,"警告","请输入用户名和密码后再注册！",QMessageBox::Ok);
        ui->userNameEdit->setFocus();
    }else{
        QSqlQuery query;
        query.exec(QString("declare @ret int; exec @ret = p_createUser '%1','%2'; select @ret").arg(name).arg(pwd));
        int isOk=0;
        QString str;
        if(query.next()){
            isOk = query.value(0).toInt();
            if(isOk==1){
                str="成功注册用户: " + name + "\n请牢记您的密码: " + pwd;
            }else if(isOk==-1){
                str="抱歉，用户名: " + name + " 已存在";
            }else{
                str="抱歉，注册失败。";
            }
        }
        QMessageBox::information(this,"消息",str,QMessageBox::Ok);
    }
}

bool LoginDialog::checkNull()
{
    name = ui->userNameEdit->text();
    pwd = ui->userPwdEdit->text();

    if(name==NULL || pwd==NULL){
        return true;
    }
    return false;
}
