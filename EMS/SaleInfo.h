#ifndef SALEINFO_H
#define SALEINFO_H

#include <QDialog>

namespace Ui {
class SaleInfo;
}

class SaleInfo : public QDialog
{
    Q_OBJECT

public:
    explicit SaleInfo(QWidget *parent = 0);
    ~SaleInfo();

private slots:
    void on_find1_clicked();

private:
    Ui::SaleInfo *ui;
};

#endif // SALEINFO_H
