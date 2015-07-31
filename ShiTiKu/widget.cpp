#include "widget.h"
#include "ui_widget.h"
#include "xlsxdocument.h"
#include "xlsxchartsheet.h"
#include <QClipboard>
#include <QMouseEvent>

QXlsx::Document xlsx("exercise.xlsx");
Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget),
    row(0),
    length(0)
{
    ui->setupUi(this);

    board = QApplication::clipboard();
    connect(QApplication::clipboard(),SIGNAL(dataChanged()),this,SLOT(findAnws()));

    row = xlsx.dimension().rowCount();
    if(row==0)
        ui->label->setText("exercise.xlsx");
}

void Widget::findAnws()
{
    //清空旧答案
    while(!anwsList.isEmpty()){
        anwsList.pop_back();
    }

    ques = board->text();   //获取复制的问题

    bool isOk=false;
    //查找问题
    for(int i=2;i<=row;i++)
    {
        if(xlsx.cellAt(i,1)->value().toString().contains(ques,Qt::CaseInsensitive))
        {
            anws = xlsx.cellAt(i,8)->value().toString();    //获取答案选项
            anws = anws + ": "+ xlsx.cellAt(QString("%1%2").arg((QChar)(anws[0].toLatin1()+2)).arg(i))->value().toString();
            ui->label->setText(anws);
            anwsList.append(anws);
            isOk = true;
        }
    }
    //如果没找到在判断题中找
    if(!isOk && xlsx.selectSheet("判断题")){
        for(int i=2;i<=xlsx.dimension().rowCount();i++){
            if(xlsx.cellAt(i,1)->value().toString().contains(ques,Qt::CaseInsensitive)){
                anws = xlsx.cellAt(i,3)->value().toString();
                ui->label->setText(anws);
                anwsList.append(anws);
            }
        }
        xlsx.selectSheet("单选题");    //重新设置为选择题
    }
    count = 0;
    length = anwsList.length();
}

void Widget::mousePressEvent(QMouseEvent *)
{
    if(length>1)
    {
        count = (++count)%length;
        ui->label->setText(anwsList.at(count));
    }
}

Widget::~Widget()
{
    delete ui;
}
