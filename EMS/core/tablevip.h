#ifndef TABLEVIP_H
#define TABLEVIP_H

#include "dataOp.h"

class TableVip : public DataOp
{
public:
    enum ItemPos{
        P_Id = 0,
        P_Uid = 1,
        P_Name = 2,
        P_Num = 3,
        P_Socre = 4
    };

    TableVip();
    QString getUid(QString id);
    QString getName(QString id);
    QString getNum(QString id);
    int getScore(QString id);
    bool setNum(QString id, QString num);
    bool setScore(QString id, int score);
    bool insertVip(QString id, QString uid, QString name,
                   QString num, int score);
private:
    QString id, uid, name, num, score;
};

#endif // TABLEVIP_H
