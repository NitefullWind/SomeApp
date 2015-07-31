#include "tableUsers.h"
#include <QDebug>

TableUsers::TableUsers():
    DataOp("users")
{
}

QString TableUsers::getUserPwd(QString name)
{
    QString pwd = getItem(name,P_Pwd);
    if(pwd==NULL){
        error = "用户名不存在";
    }
    return pwd;
}

QString TableUsers::getUserGrade(QString name)
{
    QString grade = getItem(name,P_Grade);
    if(grade==NULL){
        error = "用户名不存在";
    }
    return grade;
}

bool TableUsers::setUserPwd(QString name, QString newPwd)
{
//    QString g = getUserGrade(name);
//    if(g!=NULL){
//        if(updateRecord(name+'#'+newPwd+'#'+g)){
//            return 1;
//        }
//    }
//    return 0;
    return updateItem(name,P_Pwd,newPwd);
}

bool TableUsers::setUserGrade(QString name, QString newGrade)
{
//    QString p = getUserPwd(name);
//    if(p!=NULL)
//    {
//        if(updateRecord(name+'#'+p+'#'+newGrade)){
//            return 1;
//        }
//    }
//    return 0;
    return updateItem(name,P_Grade,newGrade);
}

bool TableUsers::createUser(QString name, QString pwd, QString grade)
{
    if(insertRecord(name+'#'+pwd+'#'+grade)){
        return 1;
    }
    if(error=="id重复"){
        error = "该用户名已存在";
    }
    return 0;
}
