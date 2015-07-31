#ifndef TABLESELL_H
#define TABLESELL_H

#include "dataOp.h"

class TableSell : public DataOp
{
public:
    enum ItemPos{
        P_Id = 0,
        P_Total = 1,
        P_Score = 2,
        P_VipId = 3,
        P_VipScore = 4
    };

    TableSell();
    ~TableSell();
    bool insertSell(QString date, double total, double score, QString vipId, double vipScore);
    double getTotal(QString id);
    double getScore(QString id);
    QString getLastNum();
};

#endif // TABLESELL_H
