#include "dataOp.h"
#include <QDebug>

DataOp::DataOp(QString fileName):
    FileOp(fileName)
{
    setFileText();
}

//插入一条新记录
bool DataOp::insertRecord(QString record)
{
    //检测是否重复id
    if(countLineBeginPos(getId(record))!=-1)
    {
        error = "id重复";
        return 0;
    }
    record += "\r\n";
    if(writeFile(record)){    //写入文件
        return 1;
    }
    return 0;
}

bool DataOp::updateRecord(QString record)
{
    QString id, oldRecord;
    id  = getId(record);
    //保存旧数据
    oldRecord = selectRecord(id);
    if(oldRecord==""){
        qDebug() << "更新失败，未找到该条数据"<< record;
        return 0;
    }
    //删除原记录
    if(!deleteRecord(getId(record))){
        return 0;
    }
    //添加新记录
    if(!insertRecord(record)){
        qDebug() << "更新失败,尝试恢复旧数据";
        if(!insertRecord(oldRecord)){
            qDebug() << "数据重大错误";
        }
        return 0;
    }else{
        return 1;
    }
    return 0;
}

bool DataOp::updateItem(QString id, int itemIndex, QString item)
{
    QString oldRecord = selectRecord(id);
    if(oldRecord==""){
        error = "未找到该条数据：" + id;
        return 0;
    }
    int index=0, n=0, len=0;
    while(index != -1){
        //找到该项元素
        if(n==itemIndex){
            len = oldRecord.indexOf('#',index+1)-index-1;
            len = (len>=0) ? len : oldRecord.length()-index-1;

            oldRecord.replace(index+1,len,item);
            if(updateRecord(oldRecord)){
                return 1;
            }
        }
        n++;
        index = oldRecord.indexOf('#',index+1);
    }
    return 0;
}

//删除一条数据
bool DataOp::deleteRecord(QString id)
{
    int lineBeginPos = countLineBeginPos(id);    //计算以id为首的行的起点

    if(lineBeginPos==-1){
        qDebug() << "找不到该条记录:"<<id;
        return 0;
    }else{
        fileText.remove(lineBeginPos,fileText.indexOf('\n',lineBeginPos)-lineBeginPos+1); //去掉这一行,注意长度+1以去掉\r
        if(coverFile(fileText)){
            return 1;
        }
    }
    return 0;
}

QString DataOp::selectRecord(QString id)
{
    int lineBeginPos = countLineBeginPos(id);
    if(lineBeginPos==-1){
        qDebug() << "找不到该条记录："<<id;
    }else{
        return fileText.mid(lineBeginPos,fileText.indexOf('\n',lineBeginPos)-lineBeginPos-1);   //不返回换行所以-1
    }
    return "";
}

//查找id在fileText的哪一行
int DataOp::countLineBeginPos(QString id)
{
    setFileText();  //每次重新计算都要刷新fileText

    int index=0, idLength;
    //查找整个fileText
    while(index!=-1){
        index = fileText.indexOf('\n',index+1);
        //一行中第一个#前为id，长度为#的位置减行首位置
        idLength = fileText.indexOf('#',index+1)-(index+1);
//        lineNum++;
        if(fileText.mid(index+1,idLength)==id){
//            qDebug() << fileText.mid(index+1,fileText.indexOf('\n',index+1)-(index+1));

            if(index==-1){  //若最后找到则为第 1 行,起点为0
                return 0;
            }else{          //其他为lineNum+1行，起点为index+1
                return index+1;
            }
        }
    }
    //没找到返回-1
    return -1;
}

//遍历真个文件返回所有行
QStringList DataOp::getRecordList()
{
    setFileText();
    QStringList recordList;
    int index=0, len=0;
    while(index !=- 1){
        len = fileText.indexOf('\n',index+1)-(index+1);
        if(len>0)   //不要最后一行空行
        {
            if(index==0){    //除了第一条记录，其他的记录去掉\r\n
                recordList.append(fileText.mid(index,len));
            }else{
                recordList.append(fileText.mid(index+1,len-1));
            }
        }
        index = fileText.indexOf('\n',index+1);
    }
    if(recordList.isEmpty()){
        error = "文件为空";
    }
    return recordList;
}

int DataOp::getLineNum()
{
    return getRecordList().length();
}

//QList <QStringList> DataOp::getRecordListToList()
//{
//    QList <QStringList> strListToList;
//    QStringList strList = getRecordList(), tempStrList;
//    QString recordStr;
//    for(int i=0;i<strList.length();i++){
//        int index = 0, len = 0;
//        recordStr = strList.at(i);      //取带符号的记录
//        tempStrList.clear();
//        while(index != -1){
//            len = recordStr.indexOf('#',index+1)-index-1;
//            len = (len>=0) ? len : recordStr.length()-index-1;

//            tempStrList.append(recordStr.mid(index+1,len));

//            index = recordStr.indexOf('#',index+1);
//        }
//        strListToList.append(tempStrList);  //中间链表追加到最终链表
//    }
//    return strListToList;
//}

//将带#号的recordList转化为不带#号的QList<QStringList>返回,参数可以指定条件，只返回满足条件的结果，无参数表示返回全部
QList <QStringList> DataOp::getRecordListToList(int itemIndex, QString item)
{
    QList <QStringList> strListToList;
    QStringList strList = getRecordList(), tempStrList;
    QString recordStr;
    for(int i=0;i<strList.length();i++){
        int index = 0, len = 0;
        recordStr = strList.at(i);      //取带符号的记录
        tempStrList.clear();
        while(index != -1){
            len = recordStr.indexOf('#',index+1)-index-1;
            len = (len>=0) ? len : recordStr.length()-index-1;

            tempStrList.append(recordStr.mid(index+1,len));

            index = recordStr.indexOf('#',index+1);
        }

        if(itemIndex!=-1 && item!="" && !tempStrList.isEmpty()){ //若参数有效
            if(tempStrList.at(itemIndex)==item){            //满足条件插入
                strListToList.append(tempStrList);
            }
            //否则不插入
        }else{          //参数无效全插入
            strListToList.append(tempStrList);  //中间链表追加到最终链表
        }

    }
    return strListToList;
}

QStringList DataOp::getItemList(QString id)
{
    QString record = selectRecord(id);
    int index = 0, len=0;
    QStringList itemList;
    while(index!=-1){
        len = record.indexOf('#',index+1)-index-1;
        len = (len>=0) ? len : record.length()-index-1;

        if(index==0){
            itemList.append(record.mid(0,record.indexOf('#',index+1)));
        }else
        {
            itemList.append(record.mid(index+1,len));
        }
        index = record.indexOf('#',index+1);
    }
    return itemList;
}

QString DataOp::getItem(QString id, int index)
{
    QStringList strList = getItemList(id);
    if(strList.length()>1){
        return strList.at(index);
    }
    return NULL;
}

void DataOp::setFileText()
{
    if(!readFile(fileText)){
        qDebug() << "读取文件失败";
    }
}

QString DataOp::getId(QString record)
{
    return record.mid(0,record.indexOf('#'));
}

bool DataOp::isExist(QString id)
{
    if(countLineBeginPos(id)!=-1){
        return 1;
    }
    return false;
}

DataOp::~DataOp()
{

}

