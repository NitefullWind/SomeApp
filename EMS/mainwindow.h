#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void setUser(QString name, QString grade);

private slots:
    void on_sellFirst_triggered();

    void on_sellSecond_triggered();

//    void on_userMan_changed();

//    void on_userLimit_changed();

    void on_updatePwd_triggered();

    void on_buyItem_triggered();

    void on_userLimit_triggered();

    void on_GoodsItem_triggered();

    void on_vipItem_triggered();

    void on_saleItem_triggered();

    void on_proInfo_triggered();


    void on_vipInfo_triggered();

private:
    Ui::MainWindow *ui;
    QString *buttonAction;
    QString userName,userGrade;
};

#endif // MAINWINDOW_H
