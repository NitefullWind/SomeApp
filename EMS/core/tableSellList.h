#ifndef TABLESELLLIST_H
#define TABLESELLLIST_H

#include "dataOp.h"
#include <QStringList>

class TableSellList : public DataOp
{
public:
    enum ItemPos{
        P_Id = 0,
        P_SerialNum = 1,
        P_Barcode = 2,
        P_Quantity = 3,
        P_Price = 4

    };
    TableSellList();
    ~TableSellList();
    bool insertSellList(QString serialNum, QString barcode, double quantity, double price);
    QList <QStringList> getSellList(QString serialNum);
};

#endif // TABLESELLLIST_H
