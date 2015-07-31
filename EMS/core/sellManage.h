#ifndef SELLMANAGE_H
#define SELLMANAGE_H

#include <QObject>
#include <QStringList>

class TableGoods;
class TableVip;
class TableSell;
class TableSellList;

class SellManage
{
public:
    SellManage();
    ~SellManage();
    bool sell();
    bool addGoods(QString barcode, QString vipId, int quantity, double price=-1);
    void returnGoods(QString serialNum);
    bool addReturnGoods(QString barcode, int quantity);
    QString getSerialNum();
    QList <QStringList> getSellInfo();
    double getTotal();
    double getScore();

    QStringList getSellList();
    QString error;
private:

    void createSerialNum(QString date);

    QString barcode, vipId;
    int quantity;
    double total, score, storeNum, vipScore, discountPercent;
    QList <QStringList> *sellInfo;
    QList <QStringList> returnList;

    TableGoods *goods;
    TableVip *vip;
    TableSell *sellFile;
    TableSellList *sellList;
    QString serialNum;
};

#endif // SELLMANAGE_H
