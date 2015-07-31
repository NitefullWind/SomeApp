#ifndef BUY2_H
#define BUY2_H

#include <QDialog>

namespace Ui {
class Buy2;
}

class Buy2 : public QDialog
{
    Q_OBJECT

public:
    explicit Buy2(QDialog *parent = 0);
    ~Buy2();

private slots:
    void on_enterButton_clicked();

    void on_cancelButton_clicked();

    void on_goodsQuantity_returnPressed();

    void on_newEnterButton_clicked();

    void on_produce_returnPressed();

    void on_newCancelButton_clicked();

private:
    Ui::Buy2 *ui;
};

#endif // BUY2_H
