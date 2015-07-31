#ifndef VIPADMINISTRATION_H
#define VIPADMINISTRATION_H

#include <QDialog>

namespace Ui {
class VIPAdministration;
}

class VIPAdministration : public QDialog
{
    Q_OBJECT

public:
    explicit VIPAdministration(QWidget *parent = 0);
    ~VIPAdministration();

private slots:
    void on_add_clicked();

    void on_rewrite_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_4_clicked();


    void on_card_4_textChanged(const QString &arg1);

private:
    Ui::VIPAdministration *ui;
};

#endif // VIPADMINISTRATION_H
