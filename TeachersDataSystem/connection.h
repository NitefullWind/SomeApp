 #ifndef CONNECTION
#define CONNECTION

#include <QSqlDatabase>
#include <QMessageBox>
#include <QSqlError>
#include <QSqlQuery>
#include <QDebug>

static bool connect()
{
    QSqlDatabase db = QSqlDatabase::addDatabase("QODBC");

    //设置dsn，注意express版本的数据库要在IP地址后加\\sqlexpress这种后缀
    QString dsn = "DRIVER={SQL SERVER};SERVER=ZZF-PC;DATABASE=jszl;"
                  "UID=zzf;PWD=123"; //192.168.100.222
    //db.setHostName(dsn);
    db.setDatabaseName(dsn);
    db.setUserName("zzf");
    db.setPassword("123");

    if(!db.open()){
        QMessageBox::critical(0,"Database connect faild.",db.lastError().text());
        return false;
    }
    return true;
}

#endif // CONNECTION

