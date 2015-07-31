#ifndef TABLEUSERS_H
#define TABLEUSERS_H

#include "dataOp.h"

class TableUsers : public DataOp
{
public:
    enum ItemPos{
        P_Name = 0,
        P_Pwd = 1,
        P_Grade = 2
    };

    TableUsers();
    QString getUserGrade(QString name);
    QString getUserPwd(QString name);
    bool setUserPwd(QString name, QString newPwd);
    bool setUserGrade(QString name, QString newGrade);
    bool createUser(QString name, QString pwd, QString grade);
private:
    QString fileName, userName, userPwd, userGrade;
};

#endif // TABLEUSERS_H
