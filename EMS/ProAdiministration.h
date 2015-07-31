#ifndef PROADIMINISTRATION_H
#define PROADIMINISTRATION_H

#include <QDialog>

namespace Ui {
class ProAdiministration;
}

class ProAdiministration : public QDialog
{
    Q_OBJECT

public:
    explicit ProAdiministration(QWidget *parent = 0);
    ~ProAdiministration();

private slots:
    void on_add_clicked();

    void on_rewrite_clicked();

    void on_update_clicked();

    void on_cancel_clicked();

    void on_goodsNum1_textChanged(const QString &arg1);

private:
    Ui::ProAdiministration *ui;
};

#endif // PROADIMINISTRATION_H
