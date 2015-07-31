#ifndef SELLSECOND_H
#define SELLSECOND_H

#include <QDialog>
#include "core/sellManage.h"

namespace Ui {
class SellSecond;
}

class SellSecond : public QDialog
{
    Q_OBJECT

public:
    explicit SellSecond(QWidget *parent = 0);
    ~SellSecond();

private slots:
    void on_pushButton_2_clicked();

    void on_pushButton_clicked();

    void on_returnBtn_clicked();

    void on_waterTxt_textChanged(const QString &arg1);

private:
    Ui::SellSecond *ui;
    SellManage sellManage;
};

#endif // SELLSECOND_H
