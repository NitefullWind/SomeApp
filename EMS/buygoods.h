#ifndef BUYGOODS_H
#define BUYGOODS_H

#include <QDialog>

namespace Ui {
class buyGoods;
}

class buyGoods : public QDialog
{
    Q_OBJECT

public:
    explicit buyGoods(QWidget *parent = 0);
    ~buyGoods();

private slots:
    void on_enterButton_clicked();

    void on_cancelButton_clicked();

    void on_goodsQuantity_returnPressed();

    void on_newEnterButton_clicked();

    void on_newCancelButton_clicked();

    void on_produce_returnPressed();

private:
    Ui::buyGoods *ui;
};

#endif // BUYGOODS_H
