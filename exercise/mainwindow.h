#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDebug>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    //按钮事件
    void on_numBtn1_clicked(){inputStr('1');setScreen();}
    void on_numBtn2_clicked(){inputStr('2');setScreen();}
    void on_numBtn3_clicked(){inputStr('3');setScreen();}
    void on_numBtn4_clicked(){inputStr('4');setScreen();}
    void on_numBtn5_clicked(){inputStr('5');setScreen();}
    void on_numBtn6_clicked(){inputStr('6');setScreen();}
    void on_numBtn7_clicked(){inputStr('7');setScreen();}
    void on_numBtn8_clicked(){inputStr('8');setScreen();}
    void on_numBtn9_clicked(){inputStr('9');setScreen();}
    void on_numBtn0_clicked(){inputStr('0');setScreen();}
    void on_sqrtBtn_clicked(){inputStr('q');setScreen();}
    void on_potBtn_clicked() {inputStr('.');setScreen();}
    void on_addBtn_clicked() {inputStr('+');setScreen();}
    void on_subBtn_clicked() {inputStr('-');setScreen();}
    void on_mulBtn_clicked() {inputStr('*');setScreen();}
    void on_divBtn_clicked() {inputStr('/');setScreen();}
    void on_sinBtn_clicked() {inputStr('s');setScreen();}
    void on_cosBtn_clicked() {inputStr('c');setScreen();}
    void on_tanBtn_clicked() {inputStr('t');setScreen();}
    void on_logBtn_clicked() {inputStr('l');setScreen();}
    void on_powBtn_clicked() {inputStr('^');setScreen();}
    void on_leftBtn_clicked(){inputStr('(');setScreen();}
    void on_rightBtn_clicked() {inputStr(')');setScreen();}
    void on_jieChengBtn_clicked(){inputStr('!');setScreen();}
    void on_cleanBtn_clicked();
    void on_equalBtn_clicked();
    void on_deleteBtn_clicked();
    void on_upButton_clicked();
    void on_downButton_clicked();

    //菜单事件
    void openFile();
    void saveFile();
    void quitApp();
private:
    Ui::MainWindow *ui;
    QString midStr;
    QString behStr;
    QString resultStr;
    QString manyMidStr;
    void inputStr(QChar c);
    bool beCalculated;
    double getNumber(QStack<double> &S);
    void calculate();
    void calStr();
    void middle();
    int great(QChar c);
    void setScreen();
    QList<QString> *record;
    int recordIndex;
    int ZF;
};

#endif // MAINWINDOW_H
