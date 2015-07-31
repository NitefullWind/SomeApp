#include "fileOp.h"
#include <QFile>
#include <QFileInfo>
#include <QDebug>

FileOp::FileOp(QString fileName)
{
    this->fileName = fileName+".txt";

    QFileInfo info(this->fileName);
    //若不存在该文件则创建
    if(!info.isFile() && createFile()){
        qDebug() << "文件不存在";
    }
}

bool FileOp::readFile(QString &text)
{
    QFile file(fileName);
    if(!file.open(QIODevice::ReadOnly)){
        qDebug() << "Read open file failed";
        return 0;
    }else{
        QTextStream stream(&file);
        text = stream.readAll();
        file.close();
        return 1;
    }
}

bool FileOp::writeFile(QString &text)
{
    QFile file(fileName);
    if(!file.open(QIODevice::WriteOnly|QIODevice::Append)){
        qDebug () << "Write open file failed";
        return 0;
    }else{
        QTextStream stream(&file);
        stream << text;
        file.close();
        return 1;
    }
}

bool FileOp::coverFile(QString &text)
{
    QFile file(fileName);
    if(!file.open(QIODevice::WriteOnly)){
        qDebug() << "Cover open file failed";
        return 0;
    }else{
        QTextStream stream(&file);
        stream << text;
        file.close();
        return 1;
    }
}

bool FileOp::createFile()
{
    QFile file(fileName);
    if(!file.open(QIODevice::WriteOnly)){
        return 0;
    }else{
        file.close();
        return 1;
    }
}

void FileOp::setFileName(QString name)
{
    fileName = name += ".txt";
}

FileOp::~FileOp()
{

}
