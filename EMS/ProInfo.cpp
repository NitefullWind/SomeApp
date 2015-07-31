#include "ProInfo.h"
#include "core/tablegoods.h"
#include "qmessagebox.h"
#include <QDebug>
#include "ui_ProInfo.h"

ProInfo::ProInfo(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ProInfo)
{
    ui->setupUi(this);
    QPalette palette;
        palette.setBrush(QPalette::Background, QBrush(QPixmap("d:/Xiaoxueqi/640-400.png")));
        this->setPalette(palette);
}

ProInfo::~ProInfo()
{
    delete ui;
}

void ProInfo::on_find_clicked()
{
    QString goodsNum = ui->lineEdit->text();
    TableGoods goods;
    if(goods.isExist(goodsNum))
    {
    ui->tableWidget->setRowCount(1);
    ui->tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->tableWidget->setItem(0, 0, new QTableWidgetItem(goodsNum));
    ui->tableWidget->setItem(0, 1, new QTableWidgetItem(goods.getName(goodsNum)));
    ui->tableWidget->setItem(0, 2, new QTableWidgetItem(QString::number(goods.getPrice(goodsNum))));
    ui->tableWidget->setItem(0, 3, new QTableWidgetItem(QString::number(goods.getScorePercent(goodsNum))));
    ui->tableWidget->setItem(0, 4, new QTableWidgetItem(QString::number(goods.getDiscoutPercent(goodsNum))));
    ui->tableWidget->setItem(0, 5, new QTableWidgetItem(goods.getProduce(goodsNum)));
    ui->tableWidget->setItem(0, 6, new QTableWidgetItem(QString::number(goods.getStoreNum(goodsNum))));
    qDebug() << goods.getName(goodsNum);
    }
    else
    {
        QMessageBox::information(this, "提示", "没有该商品！");
    }
}


