#ifndef FILEOP_H
#define FILEOP_H
#include <QObject>

class FileOp
{
public:
    FileOp(QString fileName);
    ~FileOp();
    bool readFile(QString &text);
    bool writeFile(QString &text);
    bool coverFile(QString &text);
//    bool readRecord(QString &record);
    void setFileName(QString name);
    QString error;
private:
    QString fileName;
    bool createFile();
};

#endif // FILEOP_H
