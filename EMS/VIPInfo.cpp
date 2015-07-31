
#include "VIPInfo.h"
#include "core/tablevip.h"
#include "qmessagebox.h"
#include "ui_VIPInfo.h"

VIPInfo::VIPInfo(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::VIPInfo)
{
    ui->setupUi(this);
}

VIPInfo::~VIPInfo()
{
    delete ui;
}

void VIPInfo::on_find2_clicked()
{
    QString card = ui->lineEdit->text();
    TableVip vip;
    if(vip.isExist(card))
    {
    ui->tableWidget->setRowCount(1);
    ui->tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->tableWidget->setItem(0, 0, new QTableWidgetItem(card));
    ui->tableWidget->setItem(0, 1, new QTableWidgetItem(vip.getUid(card)));
    ui->tableWidget->setItem(0, 2, new QTableWidgetItem(vip.getName(card)));
    ui->tableWidget->setItem(0, 3, new QTableWidgetItem(vip.getNum(card)));
    ui->tableWidget->setItem(0, 4, new QTableWidgetItem(QString::number((vip.getScore(card)))));
    }
    else
    {
        QMessageBox::information(this, "提示", "没有该会员卡！");
    }
}
