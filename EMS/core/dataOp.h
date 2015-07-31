#ifndef DATAOP_H
#define DATAOP_H

#include "fileOp.h"

class DataOp : public FileOp
{
public:
    DataOp(QString fileName);
    ~DataOp();
    bool insertRecord(QString record);
    bool deleteRecord(QString id);
    bool updateRecord(QString record);
    bool updateItem(QString id, int itemIndex, QString item);
    QString selectRecord(QString id);
    QStringList getItemList(QString id);
    QStringList getRecordList();
//    QList <QStringList> getRecordListToList();
    QList <QStringList> getRecordListToList(int itemIndex=-1, QString item="");
    int getLineNum();
    QString getItem(QString id, int index);
    QString getId(QString record);
    void setFileText();
    int countLineBeginPos(QString id);
    bool isExist(QString id);
private:
    QString fileText;
};

#endif // DATAOP_H
