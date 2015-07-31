#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <cmath>
#include <QStack>
#include <QDebug>
#include <QTextBlock>
#include <QFile>
#include <QFileDialog>
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    midStr="";
    behStr="";
    beCalculated=false;
    resultStr="";
    record=new QList<QString>;
    recordIndex=0;
    manyMidStr="";
    ZF = 1;
    ui->setupUi(this);

    connect(ui->openAction,SIGNAL(triggered()),this,SLOT(openFile()));
    connect(ui->saveAction,SIGNAL(triggered()),this,SLOT(saveFile()));
    connect(ui->quitAction,SIGNAL(triggered()),this,SLOT(quitApp()));
}

//输入中缀表达式
void MainWindow::inputStr(QChar c)
{
    //当上次的计算出结果没有清零时，则将上次的结果当做运算数
    if(beCalculated)
    {
        on_cleanBtn_clicked(); //清空屏幕
        if(c=='q' || c=='s' || c=='t' || c=='c' || c=='l')
        {
            midStr += c;
            midStr += resultStr;
        }
        else if(c<'0' || c>'9')
        {
            midStr = resultStr;
            midStr += c;
        }
        else{
            midStr += c;
        }
    }
    //否则当做普通的输入
    else
    {
        midStr += c;
    }
}
//清空
void MainWindow::on_cleanBtn_clicked()
{
    midStr = "";
    beCalculated=false;
    setScreen();
}

//点击"="后:
void MainWindow::on_equalBtn_clicked()
{
    //以文件或从屏幕中输入时
    if(midStr!=ui->screen->toPlainText()){
        QTextDocument allMidStr(ui->screen->toPlainText());
        //逐行计算
        int lineNum = allMidStr.lineCount();
        manyMidStr=midStr="";
        for(int i=0;i<lineNum;i++)
        {
            midStr = allMidStr.findBlockByLineNumber(i).text();
            //如果midStr非空则运算
            if(!midStr.isEmpty())
            {
                calStr();
                manyMidStr += midStr+"\n";
            }
        }
        ui->screen->setText(manyMidStr);
    }
    //避免连按"="
    if(!beCalculated){
        calStr();
        setScreen();
        manyMidStr = midStr;
        record->append(midStr);
    }
}

void MainWindow::calStr()
{
    middle();
    calculate();
    midStr = midStr + "=" + resultStr;
    beCalculated=true;
}

void MainWindow::setScreen(){
    ui->screen->setText(midStr);
}

//后缀表达式计算
void MainWindow::calculate()
{
    QStack<double> numStack;
    int i;
    double temp=0;
    bool isOk=false;
    for( i=0;i<behStr.length();i++)
    {
        char ch=behStr[i].toLatin1();
        if(ch>='0'&&ch<='9')
        {
            temp = 10*temp + (ch-'0');
            isOk=true;
            continue;
        }
        else if(ch=='-'&&behStr[i+1]>='0'&&behStr[i+1]<='9')  //遇到负数
        {
            ZF = -1;     //置负号标志为-1
        }
        else if(ch=='.'){
            int index = 0;
            while(behStr[i+1]!=' ')
            {
                index++;
                double m=behStr[i+1].toLatin1()-'0';
                m=m*pow(0.1,index);
                temp += m;
                i++;
            }
            continue;
        }
        else if(ch==' '&& isOk==true)
        {
            numStack.push(ZF*temp); //带正负号的数字入栈
            temp=0;
            ZF = 1;
            isOk=false;
            continue;
        }
        //当是操作符时
        else
        {
            if(ch=='+'){
                numStack.push(getNumber(numStack)+getNumber(numStack));
            }
            if(ch=='-'){
                double a = getNumber(numStack);
                double b = getNumber(numStack);
                numStack.push(b-a);
            }
            if(ch=='*'){
                numStack.push(getNumber(numStack)*getNumber(numStack));
            }
            if(ch=='/'){
                double a = getNumber(numStack);
                double b = getNumber(numStack);
                numStack.push(b/a);
            }
            if(ch=='^'){
                double a = getNumber(numStack);
                double b = getNumber(numStack);
                numStack.push(pow(b,a));
            }
            if(ch=='s'){
                numStack.push(sin(getNumber(numStack)));
            }
            if(ch=='c'){
                numStack.push(cos(getNumber(numStack)));
            }
            if(ch=='t'){
                numStack.push(tan(getNumber(numStack)));
            }
            if(ch=='l'){
                double n = getNumber(numStack);
                if(n>=0)
                    numStack.push(log10(n));
                else
                    midStr+="<表达式错误>";
            }
            if(ch=='q'){
                double n = getNumber(numStack);
                if(n>=0)
                    numStack.push(sqrt(n));
                else
                    midStr+="<表达式错误>";
            }
            if(ch=='!'){
                int n = getNumber(numStack);
                if(n>=0)
                {
                    double sum=1;
                    for(int j=n;j>0;j--)
                    {
                        sum*=j;
                    }
                    numStack.push(sum);
                }
                else
                    midStr+="<表达式错误>";
            }
        }
    }
    //将结果保存在resultStr中
    resultStr = QString::number(getNumber(numStack));
}
//得到栈顶元素
double MainWindow::getNumber(QStack<double> &S)
{
    //栈不空时取才数，避免溢出
    double a=0;
    if(!S.isEmpty())
    {
        a = S.top();
        S.pop();
    }
    return a;
}

//中缀转后缀
void MainWindow::middle()
{
    QStack<QChar> st;
    QChar ch;
    behStr="";
    for(int i=0;i<midStr.length();i++)
    {
        ch=midStr[i];
        if(ch>='0'&&ch<='9')//数字时
        {
            behStr += ch;
            if(midStr[i+1]!='.'&&(midStr[i+1]<'0'||midStr[i+1]>'9'))
            {
                behStr += ' ';//下个字符不是数字就加个空格
            }
        }else//字符时
        {
            if(ch=='.')        //小数点
            {
                behStr += '.';
            }
            else if(ch=='('||st.isEmpty())
            {
                st.push(ch);
            }
            else if(ch=='-'&&(midStr[i-1]<'0'||midStr[i-1]>'9'))    //负号
            {
                behStr += '-';
            }
            else if(great(ch)>great(st.top()))
            {
                st.push(ch);
            }
            else if(ch==')'&&st.top()=='(')
            {
                st.pop();
            }
            else
            {
                behStr += st.top();
                behStr += ' ';
                st.pop();
                st.push(ch);
            }
        }
    }
    while(!st.isEmpty())
    {
        behStr += st.top();
        behStr += ' ';
        st.pop();
    }
}

//优先级函数
int MainWindow::great(QChar c)
{
    if(c=='('||c==')') return 0;
    if(c=='+'||c=='-') return 1;
    if(c=='*'||c=='/') return 2;
    if(c=='!'||c=='q'||c=='^'||c=='s'||c=='c'||c=='t'||c=='l') return 4;
    return -1;
}
//退格的实现
void MainWindow::on_deleteBtn_clicked()
{
    midStr.remove(midStr.length()-1,1);
    setScreen();
}

void MainWindow::on_upButton_clicked()
{
    if(!record->isEmpty())
    {
        midStr = record->at(recordIndex = (recordIndex-1 < 0 ? record->length()-1 : recordIndex-1));
        setScreen();
    }
}
void MainWindow::on_downButton_clicked()
{
    if(!record->isEmpty())
    {
        midStr = record->at(recordIndex = ((recordIndex+1)%record->length()));
        setScreen();
    }
}

//菜单功能
void MainWindow::openFile()
{
    //选择文件
    QString path = QFileDialog::getOpenFileName(this,tr("打开需要计算的表达式文件"),"",tr("文件类型(*.txt)"));
    if(!path.isEmpty())
    {
        QFile file(path);
        //打开文件，若失败则报错
        if(!file.open(QIODevice::ReadOnly|QIODevice::Text))
        {
            QMessageBox::warning(this, tr("抱歉"),tr("打开文件失败：\n%1").arg(path));
        }
        //打开文件，成功则读取数据
        else
        {
            QTextStream data(&file);
            ui->screen->setText(data.readAll());
        }
        file.close();
    }
}
void MainWindow::saveFile()
{
    //选择保存文件路径
    QString path = QFileDialog::getSaveFileName(this,tr("将计算结果保存"),".",tr("文件类型(*.txt)"));
    if(!path.isEmpty())
    {
        QFile file(path);
        if(!file.open(QIODevice::WriteOnly|QIODevice::Text))
        {
            QMessageBox::warning(this, tr("抱歉"),tr("保存文件失败：\n%1").arg(path));
        }
        //如果文件打开成功则将结果写入文件
        else
        {
            QTextStream data(&file);
            data << manyMidStr;
        }
        file.close();
    }
}
void MainWindow::quitApp()
{
    close();
}

MainWindow::~MainWindow()
{
    delete record;
    delete ui;
}
