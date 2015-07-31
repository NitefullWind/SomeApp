#ifndef PROINFO_H
#define PROINFO_H

#include <QDialog>

namespace Ui {
class ProInfo;
}

class ProInfo : public QDialog
{
    Q_OBJECT

public:
    explicit ProInfo(QWidget *parent = 0);
    ~ProInfo();

private slots:
    void on_find_clicked();


private:
    Ui::ProInfo *ui;
};

#endif // PROINFO_H
