#include "userlimit.h"
#include "ui_userlimit.h"
#include <QMessageBox>
#include "core/tableusers.h"
#include <QDebug>

UserLimit::UserLimit(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::UserLimit)
{
    ui->setupUi(this);
//    connect(ui->addUserBtn, SIGNAL(clicked()),  this,SLOT(on_addUserBtn_clicked()));
//    connect(ui->yesBtn,     SIGNAL(clicked()),  this,SLOT(on_yesBtn_clicked()));

    QPalette palette;
        palette.setBrush(QPalette::Background, QBrush(QPixmap("d:/Xiaoxueqi/420-280.png")));
        this->setPalette(palette);
}

UserLimit::~UserLimit()
{
    delete ui;
}

void UserLimit::on_addUserBtn_clicked()
{
    ui->addUserBtn->setEnabled(false);

}

void UserLimit::on_yesBtn_clicked()
{
    QString name=ui->userNameTxt->text();
    QString password = ui->userPwdTxt->text();
    QString grade = ui->comboBox->currentText();
    TableUsers user;
    if(ui->addUserBtn->isEnabled()){
        qDebug() << name;
        if(!user.isExist(name))
        {
            QMessageBox::information(NULL,"修改用户权限","用户不存在！",QMessageBox::Ok);
        }
        else
        {
            if(user.getUserPwd(name)==password){
            user.setUserGrade(name,grade);
            QMessageBox::information(NULL,"修改用户权限","用户权限修改成功！",QMessageBox::Ok);
            }
            else
            {
                QMessageBox::information(NULL,"修改用户权限","用户密码错误！",QMessageBox::Ok);
            }
        }

    }
    else{
        if(!user.isExist(name)){
            user.createUser(name,password,grade);
            QMessageBox::information(NULL,"添加用户","添加用户成功！",QMessageBox::Ok);
            ui->addUserBtn->setEnabled(true);
            ui->userNameTxt->clear();
            ui->userPwdTxt->clear();
            ui->userNameTxt->setFocus();
            }
        else{
            QMessageBox::information(NULL,"添加用户","用户已存在！",QMessageBox::Ok);
            ui->addUserBtn->setEnabled(true);
            ui->userNameTxt->clear();
            ui->userPwdTxt->clear();
            ui->userNameTxt->setFocus();
            }

    }
}
