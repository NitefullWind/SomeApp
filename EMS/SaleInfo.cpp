#include "SaleInfo.h"
#include "ui_SaleInfo.h"
#include "core/tableSell.h"
#include "core/tableSellList.h"
#include <QDebug>
SaleInfo::SaleInfo(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SaleInfo)
{
    ui->setupUi(this);
    QPalette palette;
    palette.setBrush(QPalette::Background, QBrush(QPixmap("d:/Xiaoxueqi/640-400.png")));
    this->setPalette(palette);
}

SaleInfo::~SaleInfo()
{
    delete ui;
}

void SaleInfo::on_find1_clicked()
{
    ui->tableWidget->clear();
    QStringList tableHander;
    tableHander.append("商品流水号");
    tableHander.append("商品编码");
    tableHander.append("数量");
    tableHander.append("单价");
    tableHander.append("总金额");
    tableHander.append("积分");
    tableHander.append("销售日期");
    ui->tableWidget->setHorizontalHeaderLabels(tableHander);
    ui->tableWidget->setRowCount(20);
    ui->tableWidget->setColumnCount(7);
    ui->tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
    if(ui->checkBox->checkState() == Qt::Checked)
    {
        //tableSell t;
        QString dateBegin = ui->dateBegin->text();
        QString dateEnd = ui->dateEnd->text();
        qDebug()<<dateBegin << "      "<< dateEnd<<endl;
        ui->tableWidget->show();
    }
    else
    {
        //TableSell t;
        QString num = ui->saleNum->text();
        TableSellList sellList;
        TableSell sell;
        QList <QStringList> list;
        list = sellList.getRecordListToList(TableSellList::P_SerialNum,num);
        for(int i=0;i<list.length();i++)
        {
            for(int j=0;j<4;j++){
                ui->tableWidget->setItem(i,j,new QTableWidgetItem(list.at(i).at(j+1)));
            }
            ui->tableWidget->setItem(i,4,new QTableWidgetItem(sell.getItem(num,TableSell::P_Total)));
            ui->tableWidget->setItem(i,5,new QTableWidgetItem(sell.getItem(num,TableSell::P_Score)));
            ui->tableWidget->setItem(i,6,new QTableWidgetItem(num.mid(0,4)+"年"+num.mid(4,2)+"月"+num.mid(6,2)+"日"));
        }
    }
}
