#include "sellManage.h"
#include "tableGoods.h"
#include "tableVip.h"
#include "tableSell.h"
#include "tableSellList.h"
#include <QDate>
#include <QDebug>

SellManage::SellManage() :
    goods(new TableGoods),
    vip(new TableVip),
    sellFile(new TableSell),
    sellList(new TableSellList),
    serialNum(""),
    total(0),
    score(0),
    discountPercent(0),
    sellInfo(new QList <QStringList>)
{
    createSerialNum(QDate::currentDate().toString("yyyyMMdd"));
}

//一次出售
bool SellManage::sell()
{
    //销售记录，积分增加
    if( sellFile->insertSell(serialNum,total,score,vipId,vipScore+score)    //添加销售记录
            &&vip->setScore(vipId,vipScore+score) ){    //增加积分
        //出售成功,本次交易信息清零
        createSerialNum(QDate::currentDate().toString("yyyyMMdd")); //生成下一次交易的流水号
        total = 0;
        score = 0;
        sellInfo->clear();
        return 1;
    }
    else if(sellFile->error!=NULL){
        error = sellFile->error;
    }
    else if(goods->error!=NULL){
        error = goods->error;
    }
    else if(vip->error!=NULL){
        error = vip->error;
    }
    qDebug() << "出售失败";
    return 1;
}

//自动创建流水号
void SellManage::createSerialNum(QString date)
{
    QString lastSerial = sellFile->getLastNum().mid(0,12);
    if(lastSerial.mid(0,8)==date){
        serialNum = date + QString::number(lastSerial.mid(8,4).toInt()+1);
    }else{
        serialNum = date + "1001";
    }
}

//添加一次出售的商品的种类和数量
bool SellManage::addGoods(QString barcode, QString vipId, int quantity, double price)
{
    this->barcode = barcode;
    this->quantity = quantity;
    this->vipId = vipId;
    vipScore = vip->getScore(vipId);    //获取会员积分

    storeNum = goods->getStoreNum(barcode); //得到库存
    if(storeNum<quantity)
    {
        error =  "商品数量不足";
        return false;
    }
    //减少库存
    if(goods->setStoreNum(barcode,storeNum-quantity)){
        //计算总价
        if(price<0)     //若是默认单价则取商品单价
        {
            price = goods->getPrice(barcode);
        }
        if(vipScore>=5000 && quantity>0){   //数量大于0，即出售商品
            price *= goods->getDiscoutPercent(barcode);
        }

        int tempTotal = quantity * price;
        score += tempTotal*goods->getScorePercent(barcode);
        total += tempTotal;

        QStringList infoList;
        infoList.append(barcode);
        infoList.append(QString::number(quantity));
        infoList.append(QString::number(storeNum-quantity));
        sellInfo->append(infoList);

        sellList->insertSellList(serialNum,barcode,quantity,price);    //插入销售明细
    }

    return 1;
}


QList <QStringList> SellManage::getSellInfo()
{
    return *sellInfo;
}

void SellManage::returnGoods(QString serialNum)
{

//    total = sellFile->getTotal(serialNum);  //退货前的信息
//    score = sellFile->getScore(serialNum);

    returnList = sellList->getSellList(serialNum);
}

//添加退货商品
bool SellManage::addReturnGoods(QString barcode, int quantity)
{
    qDebug() << serialNum<< barcode << quantity;
    for(int i=0;i<returnList.length();i++){
        int maxQuantity = returnList.at(i).at(TableSellList::P_Quantity).toInt();
        if(barcode==returnList.at(i).at(TableSellList::P_Barcode)
                && quantity<=maxQuantity)
        {
            //更新可退数量
            QStringList l = returnList.at(i);
            l.removeAt(TableSellList::P_Quantity);
            l.insert(TableSellList::P_Quantity,QString::number(maxQuantity-quantity));
            returnList.removeAt(i);
            returnList.insert(i,l);

            addGoods(barcode,vipId,-quantity,returnList.at(i).at(TableSellList::P_Price).toInt());  //回库
            return 1;
        }
    }
    return 0;
}

QString SellManage::getSerialNum()
{
    return serialNum;
}

double SellManage::getTotal()
{
    return total;
}

double SellManage::getScore()
{
    return score;
}

SellManage::~SellManage()
{
    delete goods;
    delete vip;
    delete sellFile;
    delete sellList;
    delete sellInfo;
}

