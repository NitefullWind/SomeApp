#include "tableGoods.h"
#include <QDebug>

TableGoods::TableGoods():
    DataOp("goods")
{
}

QString TableGoods::getName(QString id)
{
    return getItem(id,P_Name);
}

double TableGoods::getPrice(QString id)
{
    return getItem(id,P_Price).toDouble();
}

QString TableGoods::getProduce(QString id)
{
    return getItem(id,P_Produce);
}

double TableGoods::getScorePercent(QString id)
{
    return getItem(id,P_ScorePercent).toDouble();
}

double TableGoods::getDiscoutPercent(QString id)
{
    return getItem(id,P_DiscountPercent).toDouble();
}

int TableGoods::getStoreNum(QString id)
{
    return getItem(id,P_StoreNum).toInt();
}

bool TableGoods::setStoreNum(QString id, int num)
{
    return updateItem(id,P_StoreNum,QString::number(num));
}

bool TableGoods::setDiscoutPercent(QString id, double discoutPercent)
{
    return updateItem(id,P_DiscountPercent,QString::number(discoutPercent));
}

bool TableGoods::setPrice(QString id, double price)
{
    return updateItem(id,P_Price,QString::number(price));
}

bool TableGoods::setScorePercent(QString id, double scorePercent)
{
    return updateItem(id,P_ScorePercent,QString::number(scorePercent));
}

bool TableGoods::insertGoods(QString id, QString name, double price, QString produce
                             ,double scorePercent, double discoutPercent, int storeNum)
{
    QString rec = id+'#'+name+'#'+QString::number(price)+'#'+produce+'#'
            +QString::number(scorePercent)+'#'
            +QString::number(discoutPercent)+'#'+QString::number(storeNum);
    if(insertRecord(rec)){
        return 1;
    }
    if(error=="id重复"){
        error = "该商品编号以存在";
    }
    return false;
}
