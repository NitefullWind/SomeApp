#include "tableSellList.h"

TableSellList::TableSellList():
    DataOp("sellList")
{
}

bool TableSellList::insertSellList(QString serialNum, QString barcode, double quantity, double price)
{
    QString rec = QString::number(getLineNum()) + '#' + serialNum + '#' +
                barcode + '#' + QString::number(quantity) + '#' + QString::number(price);
    return insertRecord(rec);
}

QList <QStringList> TableSellList::getSellList(QString serialNum)
{
    return getRecordListToList(P_SerialNum,serialNum);
}

TableSellList::~TableSellList()
{

}

