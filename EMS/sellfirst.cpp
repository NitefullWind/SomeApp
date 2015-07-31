#include "sellfirst.h"
#include "ui_sellfirst.h"
#include "core/tablevip.h"
#include "core/tablegoods.h"
#include "QMessageBox"
#include <QDate>


SellFirst::SellFirst(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SellFirst),
    sellManage(SellManage())
{
    ui->setupUi(this);
//    inputItem = new QString[10];
    ui->tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->timeLabel->setText(QDate::currentDate().toString("yyyy年MM月dd日"));
    ui->wateLabel->setText(sellManage.getSerialNum());

    QPalette palette;
        palette.setBrush(QPalette::Background, QBrush(QPixmap("d:/Xiaoxueqi/640-400.png")));
        this->setPalette(palette);
}

SellFirst::~SellFirst()
{
    delete ui;
}



void SellFirst::on_pushButton_clicked()
{
    QString barcode=ui->barcode->text();
    int qty = ui->sellQty->text().toInt();

    TableGoods goods;
    if(goods.isExist(barcode))
    {
        sellManage.addGoods(barcode,ui->VIPNumTxt->text(),qty);
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

void SellFirst::on_checkBtn_clicked()
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

void SellFirst::on_onSellBtn_clicked()
{
    if(ui->tableWidget->rowCount()>0)
    {
        sellManage.sell();
        ui->tableWidget->setRowCount(0);
        ui->VIPNumTxt->clear();
        ui->barcode->clear();
        ui->sellQty->clear();
        ui->tableWidget->clear();
        ui->scoreGotTxt->clear();
        ui->sumPriceLabel->setText("0");
        ui->sumScoreLabel->setText("0");
    }
}
