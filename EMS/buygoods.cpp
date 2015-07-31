#include "buygoods.h"
#include "ui_buygoods.h"
#include <QMessageBox>
#include <core/tablegoods.h>
#include <QDebug>

buyGoods::buyGoods(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::buyGoods)
{
    ui->setupUi(this);
    QPalette palette;
    palette.setBrush(QPalette::Background, QBrush(QPixmap("d:/Xiaoxueqi/640-400.png")));
    this->setPalette(palette);
}

buyGoods::~buyGoods()
{
    delete ui;
}

void buyGoods::on_enterButton_clicked()
{
    QString goodsNum = NULL ;
    QString goodsQuantity = 0;
    goodsNum = ui->goodsNum->text();
    goodsQuantity = ui->goodsQuantity->text().toLatin1();
    if(!goodsNum.isEmpty() && !goodsQuantity.isEmpty())
    {
        TableGoods goods;
        if(goods.isExist(goodsNum))
        {
            int temp = goods.getStoreNum(goodsNum);
            temp += goodsQuantity.toInt();
            if(goods.setStoreNum(goodsNum, temp))
            {
                QMessageBox::about(this,"注意","添加成功");
                ui->goodsNum->clear();
                ui->goodsQuantity->clear();
            }
            else
            {
            QMessageBox::warning(this,"注意","tianjiashibai");
            }
        }
        else
        {
             QMessageBox::warning(this,"注意","不存在商品信息，请从新商品处添加进货信息");
        }
    }
    else
    {
        QMessageBox::warning(this,"注意","信息不能为空，请填写");
    }
}

void buyGoods::on_cancelButton_clicked()
{
    this->close();
}

void buyGoods::on_goodsQuantity_returnPressed()
{
    on_enterButton_clicked();
}

void buyGoods::on_newEnterButton_clicked()
{
    QString goodsNum = ui->goodsNum2->text();
    QString goodsQuantity = ui->goodsQuantity2->text();
    QString goodsName = ui->goodsName->text();
    QString salePrice = ui->salePrice->text();
    QString scorePercent = ui->scorePercent->text();
    QString discountPercent = ui->discountPercent->text();
    QString produce = ui->produce->text();

     TableGoods goods;

         if(!goodsNum.isEmpty() && !goodsQuantity.isEmpty() && !goodsName.isEmpty()
                 && !salePrice.isEmpty() && !produce.isEmpty())
         {
             if(goodsNum.length() != 13)
             {
                 QMessageBox::warning(this,"注意","barCode is supposed to be 13 bytes");//" 商品编码需要13位");
             }
             else
             {


                 if(goods.isExist(goodsNum))
                 {
                     QMessageBox::warning(this,"注意","Goods has been existed!");//"商品已存在,请从已有商品处填写");
                 }
                 else
                 {
                     QString temp = NULL;
                     temp = goodsNum +'#'+ goodsName+'#'+ salePrice  +'#'+ produce+'#'+ scorePercent+'#' + discountPercent +'#'+ goodsQuantity.toLatin1() ;

                     goods.insertRecord(temp);
                     QMessageBox::about(this,"注意","入库成功");
                     ui->goodsNum2->clear();
                     ui->goodsQuantity2->clear();
                     ui->goodsName->clear();
                     ui->salePrice->clear();
                     ui->scorePercent->setValue(0);
                     ui->discountPercent->setValue(0);
                     ui->produce->clear();
                 }
            }
         }
         else
         {
             QMessageBox::warning(this,"注意","信息不能为空，请填写");
         }


}


void buyGoods::on_newCancelButton_clicked()
{
    this->close();
}

void buyGoods::on_produce_returnPressed()
{
    on_newEnterButton_clicked();
}
