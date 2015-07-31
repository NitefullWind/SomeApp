#include "mainwindow.h"
#include "login.h"
#include "core/tableusers.h"
#include <QApplication>
#include <QDebug>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    //TableUsers u;
    //u.insertRecord("zzf#123#1");
    //u.insertRecord("lcg#234#2");

    Login l;
    int ok = l.exec();
    MainWindow w;
    w.setUser(l.getUserName(),l.getUserGrade());
    if(ok==QDialog::Accepted)
    {
        w.show();
        return a.exec();
    }else{
        return 0;
    }
}
