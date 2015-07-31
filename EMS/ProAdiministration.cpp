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
        palette.setBrush(QPalette::Background, QBrush(QPixmap("d:/Xiaoxueqi/640-400.png")));
        this->setPalette(palette);
}

ProAdiministration::~ProAdiministration()
{
    delete ui;
}

//商品添加按钮
void ProAdiministration::on_add_clicked()
{
    QString goodsNum = ui->goodsNum->text();
    QString goodsName = ui->goodsName->text();
    QString salePrice = ui->salePrice->text();
    QString produce = ui->produce->text();
    QString scorePercent = ui->scorePercent->text();
    QString discountPercent = ui->discountPercent->text();

    QString storeNum = ui->storeNum->text();
    TableGoods goods;
    if(!goodsNum.isEmpty() && !goodsName.isEmpty() && !salePrice.isEmpty() && !scorePercent.isEmpty() && !discountPercent.isEmpty() && !produce.isEmpty() && !storeNum.isEmpty())
    {

         if(goods.isExist(goodsNum))
         {
             QMessageBox::warning(this,"提示","商品已存在！");
         }
         else
         {
             goods.insertGoods(goodsNum, goodsName, salePrice.toDouble(),produce, scorePercent.toDouble(), discountPercent.toDouble(),  storeNum.toInt());
             QMessageBox::information(this, "提示", "插入成功");
             on_rewrite_clicked();
         }

    }
    else
    {
        QMessageBox::warning(this,"提示","所有信息不能为空！");
    }
}


//商品重置按钮
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



//商品修改按钮
void ProAdiministration::on_update_clicked()
{

    TableGoods goods;
    QString goodsNum1 = ui->goodsNum1->text();
    goods.setPrice(goodsNum1, ui->salePrice1->text().toDouble());
    goods.setScorePercent(goodsNum1, ui->scorePercent1->text().toDouble());
    goods.setDiscoutPercent(goodsNum1, ui->discountPercent1->text().toDouble());
    goods.setStoreNum(goodsNum1, ui->storeNum1->text().toInt());

    QMessageBox::information(this, "提示", "修改成功");

    ui->goodsNum1->setText(NULL);
    ui->goodsName1->setText(NULL);
    ui->salePrice1->setText((NULL));
    ui->scorePercent1->setValue(0);
    ui->discountPercent1->setValue(0);
    ui->produce1->setText(NULL);
    ui->storeNum1->setText(NULL);

}


//商品删除按钮
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

    QMessageBox::information(this, "提示", "删除成功");
}


void ProAdiministration::on_goodsNum1_textChanged(const QString &arg1)
{
    QString goodsNum1 = ui->goodsNum1->text();
    TableGoods goods;
    ui->goodsName1->setText(goods.getName(goodsNum1));
    ui->salePrice1->setText(QString::number(goods.getPrice(goodsNum1)));
    ui->scorePercent1->setValue(goods.getScorePercent(goodsNum1));
    ui->discountPercent1->setValue(goods.getDiscoutPercent(goodsNum1));
    ui->produce1->setText(goods.getProduce(goodsNum1));
    ui->storeNum1->setText(QString::number(goods.getStoreNum(goodsNum1)));
}
