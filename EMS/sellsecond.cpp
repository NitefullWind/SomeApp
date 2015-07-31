#include "sellsecond.h"
#include "ui_sellsecond.h"
#include <QDate>
#include <QMessageBox>
#include "core/tablevip.h"
#include "core/tablegoods.h"
#include "core/tableSell.h"
#include "core/sellManage.h"
#include <QDebug>

SellSecond::SellSecond(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SellSecond)
{
    ui->setupUi(this);
    ui->tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->timeLabel->setText(QDate::currentDate().toString("yyyy年MM月dd日"));
    QString waterno = ui->waterTxt->text();

    QPalette palette;
        palette.setBrush(QPalette::Background, QBrush(QPixmap("d:/Xiaoxueqi/640-400.png")));
        this->setPalette(palette);
}

SellSecond::~SellSecond()
{
    delete ui;
}

void SellSecond::on_pushButton_2_clicked()
{
    QString id = ui->VIPNumTxt->text();
    TableVip v;
    if(!v.isExist(id))
    {
        QMessageBox::information(NULL,"提示","不存在该会员卡号",QMessageBox::Ok);
    }
    else{
        ui->scoreGotTxt->setText(QString::number(v.getScore(id)));
    }
}

void SellSecond::on_pushButton_clicked()
{
    QString barcode=ui->barcodeTxt->text();
    int qty = ui->returnTxt->text().toInt();

    TableGoods goods;
    if(goods.isExist(barcode))
    {
//        sellManage.addGoods(barcode,ui->VIPNumTxt->text(),qty);
        sellManage.addReturnGoods(barcode,qty);
        QList <QStringList> sellInfo = sellManage.getSellInfo();
        int row = sellInfo.length();
         ui->tableWidget->setRowCount(row);
         for(int i=0;i<row;i++)
         {
             for(int j=0;j<3;j++)
             {
                 ui->tableWidget->setItem(i,j,new QTableWidgetItem(sellInfo.at(i).at(j)));
             }
         }
         ui->sumPriceLabel->setText(QString::number(sellManage.getTotal()));
         ui->sumScoreLabel->setText(QString::number(sellManage.getScore()));
    }
    else
    {
        QMessageBox::information(this, "提示", "没有该商品！");
    }
}

void SellSecond::on_returnBtn_clicked()
{
    sellManage.sell();
    ui->tableWidget->setRowCount(0);
    ui->VIPNumTxt->clear();
    ui->barcodeTxt->clear();
    ui->returnTxt->clear();
    ui->tableWidget->clear();
    ui->scoreGotTxt->clear();
    ui->sumPriceLabel->setText("0");
    ui->sumScoreLabel->setText("0");
    ui->waterTxt->clear();
}

void SellSecond::on_waterTxt_textChanged(const QString &arg1)
{
    TableSell sell;
    if(sell.isExist(arg1)){
        sellManage.returnGoods(ui->waterTxt->text());
        ui->VIPNumTxt->setText(sell.getItem(arg1,TableSell::P_VipId));
    }else{
        ui->VIPNumTxt->clear();
    }
}
