#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "sellfirst.h"
#include "sellsecond.h"
#include "userLimit.h"
#include "userpwd.h"
#include "buygoods.h"
#include "ProAdiministration.h"
#include "ProInfo.h"
#include "VIPAdministration.h"
#include "VIPInfo.h"
#include "SaleInfo.h"
#include "core/tableusers.h"
#include <QDebug>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    //connect(ui->sellFirst,    SIGNAL(triggered()),  this,SLOT(on_sellFirst_changed()));
    //connect(ui->sellSecond,   SIGNAL(triggered()),  this,SLOT(on_sellSecond_changed()));
//    connect(ui->updatePwd,    SIGNAL(triggered()),  this,SLOT(on_updatePwd_changed()));
//    connect(ui->userLimit,    SIGNAL(triggered()),  this,SLOT(on_userLimit_triggered()));
   // connect(ui->buyItem,      SIGNAL(triggered()),  this,SLOT(on_buyItem_triggered()));
//    TableUsers ur;
//    ur.getUserGrade(userName);

    QPalette palette;
        palette.setBrush(QPalette::Background, QBrush(QPixmap("d:/Xiaoxueqi/background.png")));
        this->setPalette(palette);
}
MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_sellFirst_triggered()
{
    SellFirst *first = new SellFirst();
    first->exec();
}

void MainWindow::on_sellSecond_triggered()
{
    SellSecond *second = new SellSecond();
    second->exec();

}



void MainWindow::on_updatePwd_triggered()
{
    userPwd *pwd = new userPwd(this,userName);
    pwd->exec();

}

void MainWindow::setUser(QString name, QString grade)
{
    userName = name;
    userGrade = grade;

//    qDebug() << userGrade;
    if(userGrade=="visitor"){
       ui->buyItem->setEnabled(false);
       ui->proInfo->setEnabled(false);
       ui->GoodsItem->setEnabled(true);
       ui->vipInfo->setEnabled(false);
       ui->userLimit->setEnabled(false);
       ui->sellFirst->setEnabled(false);
       ui->sellSecond->setEnabled(false);
    }
    if(userGrade=="VIPdesigner")
    {
        ui->buyItem->setEnabled(false);
        ui->GoodsItem->setEnabled(false);
        ui->proInfo->setEnabled(false);
        ui->sellFirst->setEnabled(false);
        ui->sellSecond->setEnabled(false);
        ui->userLimit->setEnabled(false);
        ui->saleItem->setEnabled(false);
    }
    if(userGrade=="BusinessMen")
    {
        ui->userLimit->setEnabled(false);
        ui->vipInfo->setEnabled(false);
        ui->vipItem->setEnabled(false);
    }
}



void MainWindow::on_userLimit_triggered()
{
    UserLimit *l = new UserLimit();
    l->exec();

}

void MainWindow::on_buyItem_triggered()
{
    buyGoods *buy = new buyGoods();
    buy->exec();
}


void MainWindow::on_GoodsItem_triggered()
{
    ProInfo *pro = new ProInfo();
    pro->exec();
}

void MainWindow::on_vipItem_triggered()
{
    VIPInfo *vip = new VIPInfo();
    vip->exec();
}

void MainWindow::on_saleItem_triggered()
{
    SaleInfo *sale = new SaleInfo();
    sale->exec();
}

void MainWindow::on_proInfo_triggered()
{
    ProAdiministration *pro = new ProAdiministration();
    pro->exec();
}


void MainWindow::on_vipInfo_triggered()
{
    VIPAdministration *vip = new VIPAdministration();
    vip->exec();
}
