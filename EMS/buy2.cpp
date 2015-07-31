#include "buy2.h"
#include "ui_buy2.h"
#include <iostream>
#include <QMessageBox>
using namespace std;
Buy2::Buy2(QDialog *parent) :
    QDialog(parent),
    ui(new Ui::Buy2)
{
    ui->setupUi(this);
}

Buy2::~Buy2()
{
    delete ui;
}

void Buy2::on_enterButton_clicked()
{
    QString goodsNum = NULL ;
    QString goodsQuantity = NULL;
    goodsNum = ui->goodsNum->text();
    goodsQuantity = ui->goodsQuantity->text().toInt();
    if(!goodsNum.isEmpty() && !goodsQuantity.isEmpty())
    {

        //Goods goods = new Goods();
        //if(goods.isExist(barCode))
        //{
            //int temp = goods.selectNum(barCode);
            //goodsQuantity += temp;
            //goods.update(goodsNum, goodsQuantity);

            QMessageBox::about(this,"注意","添加成功");
            //delete goods;
        //}
       //else
       //{
             //QMessageBox::warning(this,"注意","不存在商品信息，请从新商品处添加进货信息");
       //}
    }
    else
    {
        QMessageBox::warning(this,"注意","信息不能为空，请填写");
    }

}

void Buy2::on_cancelButton_clicked()
{
     this->close();
}

void Buy2::on_goodsQuantity_returnPressed()
{
    on_enterButton_clicked();
}

void Buy2::on_newEnterButton_clicked()
{
    QString goodsNum = ui->goodsNum2->text();
    QString goodsQuantity = ui->goodsQuantity2->text();
    QString goodsName = ui->goodsName->text();
    QString salePrice = ui->salePrice->text();
    QString scorePercent = ui->scorePercent->text();
    QString discountPercent = ui->discountPercent->text();
    QString produce = ui->produce->text();
    if(!goodsNum.isEmpty() && !goodsQuantity.isEmpty() && !goodsName.isEmpty()
            && !salePrice.isEmpty() && !produce.isEmpty())
    {
        QString temp = NULL;
        temp = goodsNum + goodsName + salePrice + produce + scorePercent + discountPercent + produce;
        //Goods goods = new Goods();
        //goods.insert(temp);
        QMessageBox::about(this,"注意","入库成功");
    }
    else
    {
        QMessageBox::warning(this,"注意","信息不能为空，请填写");
    }

}

void Buy2::on_produce_returnPressed()
{
    on_newEnterButton_clicked();
}

void Buy2::on_newCancelButton_clicked()
{
    this->close();
}
