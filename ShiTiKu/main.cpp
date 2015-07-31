#include "widget.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Widget w;

    w.setWindowOpacity(0.9);    //透明度
    w.setWindowFlags(Qt::WindowStaysOnTopHint); //始终在最前

    w.show();

    return a.exec();
}
