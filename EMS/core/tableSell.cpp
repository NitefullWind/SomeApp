#include "tableSell.h"
#include <QStringList>
#include <QDebug>

TableSell::TableSell():
    DataOp("sell")
{
}

bool TableSell::insertSell(QString id, double total, double score, QString vipId, double vipScore)
{
    QString rec = id + '#' + QString::number(total) + '#' + QString::number(score) + '#'
                    + vipId + '#' + QString::number(vipScore);
    if(insertRecord(rec)){
        return 1;
    }
    if(error=="id重复"){
        error = "销售流水号重复";
    }
    return 0;
}

double TableSell::getScore(QString id)
{
    return getItem(id,P_Score).toDouble();
}

double TableSell::getTotal(QString id)
{
    return getItem(id,P_Total).toDouble();
}

QString TableSell::getLastNum()
{
    QStringList recList = getRecordList();
    if(recList.length()>0){
        return recList.last().mid(0,12);
    }
    return "";
}

TableSell::~TableSell()
{

}

