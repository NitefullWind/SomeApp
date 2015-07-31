#include "mainwindow.h"
#include "logindialog.h"
#include "connection.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    if(!connect()){
        return 0;
    }

    MainWindow w;
    LoginDialog dlg;
    if(dlg.exec()==QDialog::Accepted){
        w.setUserName(dlg.getUsetName());
        w.show();
        return a.exec();
    }else{
        return 0;
    }

}
