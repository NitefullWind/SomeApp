#ifndef VIPINFO_H
#define VIPINFO_H

#include <QDialog>

namespace Ui {
class VIPInfo;
}

class VIPInfo : public QDialog
{
    Q_OBJECT

public:
    explicit VIPInfo(QWidget *parent = 0);
    ~VIPInfo();

private slots:
    void on_find2_clicked();

private:
    Ui::VIPInfo *ui;
};

#endif // VIPINFO_H
