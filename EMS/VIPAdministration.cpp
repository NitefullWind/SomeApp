
#include "VIPAdministration.h"
#include "core/tablevip.h"
#include "qmessagebox.h"
#include "ui_VIPAdministration.h"

VIPAdministration::VIPAdministration(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::VIPAdministration)
{
    ui->setupUi(this);
    QPalette palette;
        palette.setBrush(QPalette::Background, QBrush(QPixmap("d:/Xiaoxueqi/640-400.png")));
        this->setPalette(palette);
}

VIPAdministration::~VIPAdministration()
{
    delete ui;
}

//会员添加按钮
void VIPAdministration::on_add_clicked()
{
    QString card_2 = ui->card_2->text();
    QString idCard_2 = ui->idCard_2->text();
    QString name_2 = ui->name_2->text();
    QString phoneNumber_2 = ui->phoneNumber_2->text();
    QString score_2 = ui->score_2->text();
    TableVip vip;
    if(!card_2.isEmpty() && !idCard_2.isEmpty() && !name_2.isEmpty() && !phoneNumber_2.isEmpty() && !score_2.isEmpty())
    {
        if(vip.isExist(card_2))
        {
            QMessageBox::warning(this,"提示","会员已存在！");
        }
        else{
        vip.insertVip(card_2, idCard_2, name_2, phoneNumber_2, score_2.toInt());
        QMessageBox::information(this, "提示", "添加完成");
        on_rewrite_clicked();
        }
    }
    else
    {
        QMessageBox::warning(this,"提示","所有信息不能为空！");
    }
}


//会员重置按钮
void VIPAdministration::on_rewrite_clicked()
{
    ui->card_2->setText(NULL);
    ui->idCard_2->setText(NULL);
    ui->name_2->setText((NULL));
    ui->phoneNumber_2->setText((NULL));
    ui->score_2->setText((NULL));
}


//会员修改按钮
void VIPAdministration::on_pushButton_3_clicked()
{
    QString card_4 = ui->card_4->text();
    TableVip vip;

    vip.setNum(card_4, ui->phoneNumber_4->text());
    vip.setScore(card_4, ui->score_4->text().toInt());

    QMessageBox::information(this, "提示", "修改完成");

    ui->card_4->setText(NULL);
    ui->idCard_4->setText(NULL);
    ui->name_4->setText(NULL);
    ui->phoneNumber_4->setText((NULL));
    ui->score_4->setText(NULL);
}


//会员删除按钮
void VIPAdministration::on_pushButton_4_clicked()
{
    QString card_4 = ui->card_4->text();
    TableVip vip;
    vip.deleteRecord(card_4);

    ui->card_4->setText(NULL);
    ui->idCard_4->setText(NULL);
    ui->name_4->setText(NULL);
    ui->phoneNumber_4->setText((NULL));
    ui->score_4->setText(NULL);

    QMessageBox::information(this, "提示", "删除完成");
}

void VIPAdministration::on_card_4_textChanged(const QString &arg1)
{
    QString card_4 = ui->card_4->text();
    TableVip vip;
    ui->idCard_4->setText(vip.getUid(card_4));
    ui->name_4->setText(vip.getName(card_4));
    ui->phoneNumber_4->setText(vip.getNum(card_4));
    ui->score_4->setText(QString::number(vip.getScore(card_4)));
}
