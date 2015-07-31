#include "login.h"
#include "ui_login.h"
#include "mainwindow.h"
#include "core/tableusers.h"
#include <QDebug>
#include <QMessageBox>

Login::Login(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Login)
{
    ui->setupUi(this);

    QPalette palette;
        palette.setBrush(QPalette::Background, QBrush(QPixmap("d:/Xiaoxueqi/login.png")));
        this->setPalette(palette);
}

Login::~Login()
{
    delete ui;
}

void Login::on_loginButton_clicked()
{
    name = ui->userText->text();
    pwd = ui->pwdText->text();
    TableUsers u;
    if(name==NULL || pwd==NULL){
        QMessageBox::information(NULL,"Not Found","用户名或密码不能为空",QMessageBox::Ok);
    }else{
        if(pwd==u.getUserPwd(name))
        {
            grade =  u.getUserGrade(name);
            qDebug() << pwd<<u.getUserPwd(name);
            QDialog::accept();
            return ;
        }else
        {
            QMessageBox::information(NULL,"Not Found","用户名或密码不正确",QMessageBox::Ok);
            ui->userText->clear();
            ui->pwdText->clear();
            ui->userText->setFocus();
        }
    }
//    QDialog::reject();
}

void Login::on_cancelButton_clicked()
{
    QDialog::reject();
}


QString Login::getUserName()
{
    return name;
}

QString Login::getUserGrade()
{
    return grade;
}
