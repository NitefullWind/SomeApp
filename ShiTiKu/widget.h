#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>

namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();
    void mousePressEvent(QMouseEvent *);
private slots:
    void findAnws();

private:
    Ui::Widget *ui;
    QClipboard *board;
    QString ques,anws;
    QStringList anwsList;
    int row, count, length;
};

#endif // WIDGET_H
