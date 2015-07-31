#ifndef SELLFIRST_H
#define SELLFIRST_H

#include <QDialog>

#include "core/sellManage.h"

namespace Ui {
class SellFirst;
}

class SellFirst : public QDialog
{
    Q_OBJECT

public:
    explicit SellFirst(QWidget *parent = 0);
    ~SellFirst();

private slots:

    void on_pushButton_clicked();

    void on_checkBtn_clicked();

    void on_onSellBtn_clicked();

private:
    Ui::SellFirst *ui;
    QString *inputItem;
    SellManage sellManage;
};

#endif // SELLFIRST_H
