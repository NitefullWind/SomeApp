#include "ProAdiministration.h"
#include "ui_ProAdiministration.h"
#include <QMessageBox>
#include "core/tablegoods.h"

ProAdiministration::ProAdiministration(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ProAdiministration)
{
    ui->setupUi(this);
    QPalette palette;
        palette.setBrush(QPalette::Background, QBrush(QPixmap("C:/Users/lear/Desktop/640-400.png")));
        this->setPalette(palette);
}

ProAdiministration::~ProAdiministration()
{
    delete ui;
}

//��Ʒ���Ӱ�ť
void ProAdiministration::on_add_clicked()
{
    QString goodsNum = ui->goodsNum->text();
    QString goodsName = ui->goodsName->text();
    QString salePrice = ui->salePrice->text();
    QString produce = ui->produce->text();
    QString scorePercent = ui->scorePercent->text();
    QString discountPercent = ui->discountPercent->text();

    QString storeNum = ui->storeNum->text();
    if(!goodsNum.isEmpty() && !goodsName.isEmpty() && !salePrice.isEmpty() && !scorePercent.isEmpty() && !discountPercent.isEmpty() && !produce.isEmpty() && !storeNum.isEmpty())
    {
        TableGoods goods;
        goods.insertGoods(goodsNum, goodsName, salePrice.toDouble(),produce, scorePercent.toDouble(), discountPercent.toDouble(),  storeNum.toInt());
        QMessageBox::information(this, "提示", "插入成功");
    }
}


//��Ʒ���ð�ť
void ProAdiministration::on_rewrite_clicked()
{
    ui->goodsNum->setText(NULL);
    ui->goodsName->setText(NULL);
    ui->salePrice->setText((NULL));
    ui->scorePercent->setValue(0);
    ui->discountPercent->setValue(0);
    ui->produce->setText(NULL);
    ui->storeNum->setText(NULL);
}



//��Ʒ�޸İ�ť
void ProAdiministration::on_update_clicked()
{
    QString goodsNum1 = ui->goodsNum1->text();
    TableGoods goods;
    //QString storeNum = goods.getStroeNum(goodsNum1);
    ui->goodsName1->setText(goods.getName(goodsNum1));
    ui->salePrice1->setText(QString::number(goods.getPrice(goodsNum1)));
    ui->scorePercent1->setValue(goods.getScorePercent(goodsNum1));
    ui->discountPercent1->setValue(goods.getDiscoutPercent(goodsNum1));
    ui->produce1->setText(goods.getProduce(goodsNum1));
    ui->storeNum1->setText(QString::number(goods.getStoreNum(goodsNum1)));

    goods.setPrice(goodsNum1, ui->salePrice1->text().toDouble());
    goods.setScorePercent(goodsNum1, ui->scorePercent1->text().toDouble());
    goods.setDiscoutPercent(goodsNum1, ui->discountPercent1->text().toDouble());
    goods.setStoreNum(goodsNum1, ui->storeNum1->text().toInt());

    QMessageBox::information(this, "好的", "成了");

}


//��Ʒɾ����ť
void ProAdiministration::on_cancel_clicked()
{
    QString goodsNum1 = ui->goodsNum1->text();
    TableGoods goods;
    goods.deleteRecord(goodsNum1);

    ui->goodsNum1->setText(NULL);
    ui->goodsName1->setText(NULL);
    ui->salePrice1->setText((NULL));
    ui->scorePercent1->setValue(0);
    ui->discountPercent1->setValue(0);
    ui->produce1->setText(NULL);
    ui->storeNum1->setText(NULL);

    QMessageBox::information(this, "��ʾ", "ɾ������");
}

