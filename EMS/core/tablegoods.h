#ifndef TABLEGOODS_H
#define TABLEGOODS_H

#include "dataOp.h"

class TableGoods : public DataOp
{
public:
    enum ItemPos{
        P_Barcode = 0,
        P_Name = 1,
        P_Price = 2,
        P_Produce = 3,
        P_ScorePercent = 4,
        P_DiscountPercent = 5,
        P_StoreNum = 6
    };

    TableGoods();
    QString getName(QString id);
    double getPrice(QString id);
    QString getProduce(QString id);
    double getScorePercent(QString id);
    double getDiscoutPercent(QString id);
    int getStoreNum(QString id);
    bool setStoreNum(QString id, int num);
    bool setPrice(QString id, double price);
    bool setScorePercent(QString id, double scorePercent);
    bool setDiscoutPercent(QString id, double discoutPercent);
    bool insertGoods(QString id, QString name, double price, QString produce,
                     double scorePercent, double discoutPercent, int storeNum);

private:
    QString barcode, name, price, produce;
    QString scorePercent, discoutPercent, storeNum;
};

#endif // TABLEGOODS_H
