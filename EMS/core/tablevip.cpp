#include "tableVip.h"

TableVip::TableVip():
    DataOp("vip")
{
}

QString TableVip::getName(QString id)
{
    return getItem(id,P_Name);
}

QString TableVip::getUid(QString id)
{
    return getItem(id,P_Uid);
}

QString TableVip::getNum(QString id)
{
    return getItem(id,P_Num);
}

int TableVip::getScore(QString id)
{
    return getItem(id,P_Socre).toInt();
}

bool TableVip::setNum(QString id, QString num)
{
    return updateItem(id,P_Num,num);
}

bool TableVip::setScore(QString id, int score)
{
    return updateItem(id,P_Socre,QString::number(score));
}

bool TableVip::insertVip(QString id, QString uid, QString name, QString num, int score)
{
    QString rec = id + '#' + uid + '#' + name + '#' + num + '#' + QString::number(score);
    if(insertRecord(rec)){
        return 1;
    }
    if(error=="id重复"){
        error = "该Vip卡号已存在";
    }
}
