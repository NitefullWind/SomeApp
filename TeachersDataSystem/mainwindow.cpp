#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "connection.h"
#include "logindialog.h"
#include <QSqlTableModel>
#include <QSqlRecord>
#include <QInputDialog>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    id("")
{
    ui->setupUi(this);

    ui->tableView->setFocus();      //获取焦点
    ui->stackedWidget->setCurrentIndex(0);
    ui->tableView->setMouseTracking(true);  //开启鼠标追踪
//    ui->tableView->setSelectionMode(QAbstractItemView::SingleSelection);    //只选择单行
    ui->tableView->setSelectionBehavior(QAbstractItemView::SelectRows); //选择整行


    model = new QSqlTableModel;
    model->setTable("view_data");

    teacherIdModel = new QSqlQueryModel;
    classIdModel = new QSqlQueryModel;
    courseIdModel = new QSqlQueryModel;
    typeIdModel = new QSqlQueryModel;
    updateModel();

    //初始化类型选择框
    QSqlQueryModel *typeModel = new QSqlQueryModel;
    typeModel->setQuery("select typ_Name from tbl_type");
    ui->selTypeComboBox->setModel(typeModel);
    ui->selTypeComboBox->setCurrentIndex(-1);
    ui->selTypeComboBox->setCurrentText("选择类型");

    //初始化班级选择框
    QSqlQueryModel *classNameModel = new QSqlQueryModel;
    classNameModel->setQuery("select cla_shortName from tbl_class");
    ui->selClassComBox->setModel(classNameModel);
    ui->selClassComBox->setCurrentIndex(-1);
    ui->selClassComBox->setCurrentText("选择班级");

    //初始化教师选择框
    QSqlQueryModel *teacherModel = new QSqlQueryModel;
    teacherModel->setQuery("select tea_Name from tbl_teacher");
    ui->selTeachComBox->setModel(teacherModel);
    ui->selTeachComBox->setCurrentIndex(-1);
    ui->selTeachComBox->setCurrentText("选择教师");

    //初始化日期选择框
    QSqlQueryModel *dateModel = new QSqlQueryModel;
    dateModel->setQuery("select dat_Date from tbl_data");
    ui->selDateComBox->setModel(dateModel);
    ui->selDateComBox->setCurrentIndex(-1);
    ui->selDateComBox->setCurrentText("选择日期");

    model->select();
    ui->tableView->setModel(model);

    ui->userQuitLoginBtn->setToolTip("点击重新登录");
    connect(ui->actionChangePwd,SIGNAL(triggered()),this,SLOT(showNewPwdInputBox()));
}

MainWindow::~MainWindow()
{
    delete model,queryModel,teacherIdModel,courseIdModel,typeIdModel;
    delete ui;
}

void MainWindow::on_selTableComBox_currentIndexChanged(const QString &text)
{
    ui->selTeachComBox->setCurrentText("选择教师");
    ui->selTypeComboBox->setCurrentText("选择类型");
    ui->selTypeComboBox->setEnabled(false); //不可选择文档类型
    ui->selClassComBox->setCurrentText("选择班级");
    ui->selClassComBox->setEnabled(false);  //不可选择班级
    ui->selDateComBox->setCurrentText("选择日期");
    ui->selDateComBox->setEnabled(false);

    model = new QSqlTableModel;
    if(text=="教师信息"){
        model->setTable("view_teacher");
    }else if(text=="班级信息"){
        ui->selClassComBox->setEnabled(true);  //可选择班级
        model->setTable("view_class");
    }else if(text=="授课信息"){
        ui->selClassComBox->setEnabled(true);  //可选择班级
        model->setTable("view_course");
    }else if(text=="文档信息"){
        ui->selClassComBox->setEnabled(true);  //可选择班级
        ui->selTypeComboBox->setEnabled(true);  //可选择文档类型
        ui->selDateComBox->setEnabled(true);
        model->setTable("view_data");
    }else{
        model->clear();
    }
    model->select();
    ui->tableView->setModel(model);
}

//根据班名选择
void MainWindow::on_selClassComBox_currentIndexChanged(const QString &text)
{
    if(text!="")
    {
        queryModel = new QSqlQueryModel;
        queryModel->setQuery(QString("exec p_selectByClass_"+ model->tableName()+ " %1").arg(text));
        ui->tableView->setModel(queryModel);
    }

}

//根据教师名选择
void MainWindow::on_selTeachComBox_currentIndexChanged(const QString &text)
{
    if(text!="")
    {
        queryModel = new QSqlQueryModel;
        queryModel->setQuery(QString("exec p_selectByTName_"+model->tableName() + " %1").arg(text));
        ui->tableView->setModel(queryModel);
    }
}

//根据类型名选择
void MainWindow::on_selTypeComboBox_currentIndexChanged(const QString &text)
{
    if(text!="")
    {
        queryModel = new QSqlQueryModel;
        queryModel->setQuery(QString("exec p_selectByType %1").arg(text));
        ui->tableView->setModel(queryModel);
    }
}

//根据日期选择
void MainWindow::on_selDateComBox_currentIndexChanged(const QString &text)
{
    if(text!="")
    {
        queryModel = new QSqlQueryModel;
        queryModel->setQuery(QString("exec p_selectByDate '%1'").arg(text));
        ui->tableView->setModel(queryModel);
    }
}

//点击重置按钮刷新时
void MainWindow::on_freshBtn_clicked()
{
    //各选择框初始化
    ui->selClassComBox->setCurrentText("选择班名");
    ui->selTeachComBox->setCurrentText("选择教师");
    ui->selTypeComboBox->setCurrentText("选择类型");
    ui->selDateComBox->setCurrentText("选择日期");

    //重新设置表格内容为原来的Model
    ui->tableView->setModel(model);
}


//查询按钮
void MainWindow::on_selectBtn_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);
}

//删除按钮
void MainWindow::on_delBtn_clicked()
{
    QItemSelectionModel *selection = ui->tableView->selectionModel();   //选中的模型
    QModelIndexList selected = selection->selectedRows();   //选中的行
    if(!selected.length()){//若未选中任何行
        QMessageBox::critical(0,"警告","请选中要删除的行！");
        return;
    }
    if(QMessageBox::question(0,"警告","即将删除 "+QString::number(selected.count())
                             +" 条数据信息\n删除后不可恢复，确定要继续?",QMessageBox::Ok|QMessageBox::Cancel)==QMessageBox::Ok){
        qDebug() << " ";
        const QAbstractItemModel *selectedModel = selection->model();
        bool isOk=true;
        QSqlQuery q;
        foreach (QModelIndex index, selected) {
            id = selection->model()->data(selectedModel->index(index.row(),0)).toString();  //获取选中行的id
            if(!q.exec(QString("exec p_del"+getTableName()+" '%1'").arg(id))){
                isOk=false;
            }
        }
        if(!isOk){
            QMessageBox::critical(0,"警告","删除过程中出错",q.lastError().text());
        }
        id = "";
        updateModel();
        model->select();
    }
}

//插入按钮
void MainWindow::on_insertBtn_clicked()
{
    int byIndex = ui->selTableComBox->currentIndex();
    ui->toolBox->setCurrentIndex(byIndex);
    setToolBoxElsePageNotEnabled(byIndex);
    ui->stackedWidget->setCurrentIndex(1);
    isNewRecord = true;
}

//修改按钮
void MainWindow::on_updateBtn_clicked()
{
    QItemSelectionModel *selection = ui->tableView->selectionModel();   //选中的模型
    QModelIndexList selected = selection->selectedRows();   //选中的行

    if(!selected.length()){//若未选中任何行
        QMessageBox::critical(0,"警告","请选中要修改的行！");
        return;
    }

    const QAbstractItemModel *selectedModel = selection->model();
    id = selection->model()->data(selectedModel->index(selected.at(0).row(),0)).toString();  //获取选中行的id

    int byIndex = ui->selTableComBox->currentIndex();
    ui->toolBox->setCurrentIndex(byIndex);
    setToolBoxElsePageNotEnabled(byIndex);  //设置只有当前页可操作
    ui->stackedWidget->setCurrentIndex(1);

    QSqlQuery q;

    //初始化各组建为原始值
    switch (byIndex) {
    case 0:
        q.exec(QString("select * from tbl_data where dat_ID='%1'").arg(id));
        if(q.first()){
            ui->dataNameEdit->setText(q.value(1).toString());
            ui->courseIDComBox->setCurrentText(q.value(2).toString());
            ui->typeIDComBox->setCurrentText(q.value(3).toString());
            ui->fileNameEdit->setText(q.value(4).toString());
            ui->dataLeveComBox->setCurrentText(q.value(5).toString());
            ui->dataURLEdit->setText(q.value(7).toString());
        }
        break;
    case 1:
        q.exec(QString("select * from tbl_teacher where tea_ID='%1'").arg(id));
        if(q.first()){
            ui->teaIdEdit->setText(q.value(0).toString());
            ui->teaNameEdit->setText(q.value(1).toString());
            ui->teaTitleEdit->setText(q.value(2).toString());
            ui->teaSpecEdit->setText(q.value(3).toString());
            ui->teaNumEdit->setText(q.value(4).toString());
        }
        ui->teaIdEdit->setReadOnly(true);
        break;
    case 2:
        q.exec(QString("select * from tbl_class where cla_ID='%1'").arg(id));
        if(q.first()){
            ui->classIdEdit->setText(q.value(0).toString());
            ui->classNameEdit->setText(q.value(1).toString());
            ui->classSNameEdit->setText(q.value(2).toString());
            ui->classTeachIDComBox->setCurrentText(q.value(3).toString());
        }
        ui->classIdEdit->setReadOnly(true);
        break;
    case 3:
        q.exec(QString("select * from tbl_course where cou_ID='%1'").arg(id));
        if(q.first()){
            ui->courseIdEdit->setText(q.value(0).toString());
            ui->courseTeachIDComBox->setCurrentText(q.value(1).toString());
            ui->courseClassIDComBox->setCurrentText(q.value(2).toString());
            ui->courseHourSpinBox->setValue(q.value(3).toInt());
            ui->courseExaFEdit->setText(q.value(4).toString());
        }
        ui->courseIdEdit->setReadOnly(true);
        break;
    default:
        break;
    }
    isNewRecord = false;
}

//确定按钮
void MainWindow::on_manageSureBtn_clicked()
{
    QSqlQuery q;
    QString sqlStr;
    if(isNewRecord) //是新数据则执行插入
    {
        switch (ui->toolBox->currentIndex()) {
        case 0:
            sqlStr=QString("exec p_insertData '%1','%3','%4','%5','%6','%7'")
                       .arg(ui->dataNameEdit->text())
                       .arg(ui->courseIDComBox->currentText()).arg(ui->typeIDComBox->currentText())
                       .arg(ui->fileNameEdit->text()).arg(ui->dataLeveComBox->currentText())
                       .arg(ui->dataURLEdit->text());
            break;
        case 1 :
            sqlStr=QString("exec p_insertTeacher '%1','%2','%3','%4','%5'")
                    .arg(ui->teaIdEdit->text()).arg(ui->teaNameEdit->text())
                    .arg(ui->teaTitleEdit->text()).arg(ui->teaSpecEdit->text())
                    .arg(ui->teaNumEdit->text());
            break;
        case 2:
            sqlStr=QString("exec p_insertClass '%1','%2','%3','%4'")
                    .arg(ui->classIdEdit->text()).arg(ui->classNameEdit->text())
                    .arg(ui->classSNameEdit->text()).arg(ui->classTeachIDComBox->currentText());
            break;
        case 3:
            sqlStr=QString("exec p_insertCourse '%1','%2','%3','%4','%5'")
                    .arg(ui->courseIdEdit->text()).arg(ui->courseTeachIDComBox->currentText())
                    .arg(ui->courseClassIDComBox->currentText()).arg(ui->courseHourSpinBox->value())
                    .arg(ui->courseExaFEdit->text());
            break;
        case 4:
            sqlStr=QString("exec p_insertType '%1','%2'")
                    .arg(ui->typeName->text()).arg(ui->typeForm->text());
            break;
        default:
            break;
        }
        if(!q.exec(sqlStr)){
            qDebug() << q.lastError();
        }
    }else if(id!=""){   //不是新数据且id不为空则执行修改
        switch (ui->toolBox->currentIndex()) {
        case 0:
            sqlStr=QString("exec p_updateData '%1','%2','%3','%4','%5','%6','%7'")
                        .arg(id).arg(ui->dataNameEdit->text())
                       .arg(ui->courseIDComBox->currentText()).arg(ui->typeIDComBox->currentText())
                       .arg(ui->fileNameEdit->text()).arg(ui->dataLeveComBox->currentText())
                       .arg(ui->dataURLEdit->text());
            break;
        case 1 :
            sqlStr=QString("exec p_updateTeacher '%1','%2','%3','%4','%5'")
                    .arg(ui->teaIdEdit->text()).arg(ui->teaNameEdit->text())
                    .arg(ui->teaTitleEdit->text()).arg(ui->teaSpecEdit->text())
                    .arg(ui->teaNumEdit->text());
            ui->teaIdEdit->setReadOnly(false);      //重新设置可编辑
            break;
        case 2:
            sqlStr=QString("exec p_updateClass '%1','%2','%3','%4'")
                    .arg(ui->classIdEdit->text()).arg(ui->classNameEdit->text())
                    .arg(ui->classSNameEdit->text()).arg(ui->classTeachIDComBox->currentText());
            ui->classIdEdit->setReadOnly(false);
            break;
        case 3:
            sqlStr=QString("exec p_updateCourse '%1','%2','%3','%4','%5'")
                    .arg(ui->courseIdEdit->text()).arg(ui->courseTeachIDComBox->currentText())
                    .arg(ui->courseClassIDComBox->currentText()).arg(ui->courseHourSpinBox->value())
                    .arg(ui->courseExaFEdit->text());
            ui->courseIdEdit->setReadOnly(false);
            break;
        default:
            break;
        }
        if(!q.exec(sqlStr)){
            qDebug() << q.lastError();
        }
    }
    id ="";
    updateModel();
    model->select();
}

//鼠标悬停显示教师名
//void MainWindow::on_teachIDComBox_currentIndexChanged(const QString &text)
//{
//    QSqlQuery q;
//    if(q.exec(QString("select tea_Name from tbl_teacher where tea_id=%1")
//              .arg(text))){
//        if(q.next())
//            ui->teachIDComBox->setToolTip(q.value(0).toString());
//    }
//    ui->dataURLEdit->setText("D:\\"+text);
//}
void MainWindow::on_classTeachIDComBox_currentIndexChanged(const QString &text)
{
    QSqlQuery q;
    if(q.exec(QString("select tea_Name from tbl_teacher where tea_id='%1'")
              .arg(text))){
        if(q.next())
            ui->classTeachIDComBox->setToolTip(q.value(0).toString());
    }
}
void MainWindow::on_courseTeachIDComBox_currentIndexChanged(const QString &text)
{
    QSqlQuery q;
    if(q.exec(QString("select tea_Name from tbl_teacher where tea_id='%1'")
              .arg(text))){
        if(q.next())
            ui->courseTeachIDComBox->setToolTip(q.value(0).toString());
    }
}

//鼠标悬停显示班级名和教师名
void MainWindow::on_courseIDComBox_currentIndexChanged(const QString &text)
{
    QSqlQuery q;
    if(q.exec(QString("select 班级名称,教师姓名 from view_course where 课程代码='%1'")
              .arg(text))){
        if(q.next())
            ui->courseIDComBox->setToolTip(q.value(0).toString()+"("+q.value(1).toString()+")");
    }
    if(q.exec(QString("select tea_ID from tbl_course where cou_ID='%1'").arg(text))){
        if(q.next()){
            ui->dataURLEdit->setText("D:\\"+q.value(0).toString());
        }
    }
}
void MainWindow::on_courseClassIDComBox_currentIndexChanged(const QString &text)
{
    QSqlQuery q;
    if(q.exec(QString("select cla_Name from tbl_class where cla_id=%1")
              .arg(text))){
        if(q.next())
            ui->courseClassIDComBox->setToolTip(q.value(0).toString());
    }
}

//鼠标悬停显示类型名
void MainWindow::on_typeIDComBox_currentIndexChanged(const QString &text)
{
    QSqlQuery q;
    if(q.exec(QString("select typ_Name,typ_Form from tbl_type where typ_id=%1")
              .arg(text))){
        if(q.next())
            ui->typeIDComBox->setToolTip(q.value(0).toString()+ "(" +q.value(1).toString()+")");
    }
}

//根据索引返回表名
QString MainWindow::getTableName()
{
    int byIndex;
    if(ui->stackedWidget->currentIndex()==0)
        byIndex=ui->selTableComBox->currentIndex();
    else if(ui->stackedWidget->currentIndex()==1)
        byIndex=ui->toolBox->currentIndex();
    switch (byIndex) {
    case 0:
        return "Data";
    case 1:
        return "Teacher";
    case 2:
        return "Class";
    case 3:
        return "Course";
    case 4:
        return "Type";
    default:
        return "";
    }
}

//根据索引，设置toolBox中的其他页不可选择
void MainWindow::setToolBoxElsePageNotEnabled(int index)
{
    for(int i=0;i<ui->toolBox->count();i++){
        if(i!=index){
            ui->toolBox->setItemEnabled(i,false);
        }else{
            ui->toolBox->setItemEnabled(i,true);
        }
    }
}

//设置及刷新各个model
void MainWindow::updateModel()
{
    setTeacherIdModel();
    setCourseIdModel();
    setTypeIdModel();
    setClassIdModel();
}
void MainWindow::setTeacherIdModel()
{
    teacherIdModel->setQuery("select tea_ID from tbl_teacher");
//    ui->teachIDComBox->setModel(teacherIdModel);
    ui->classTeachIDComBox->setModel(teacherIdModel);
    ui->courseTeachIDComBox->setModel(teacherIdModel);
}
void MainWindow::setClassIdModel()
{
    classIdModel->setQuery("select cla_ID from tbl_class");
    ui->courseClassIDComBox->setModel(classIdModel);
}
void MainWindow::setCourseIdModel()
{
    courseIdModel->setQuery("select cou_ID from tbl_course");
    ui->courseIDComBox->setModel(courseIdModel);
    ui->courseClassIDComBox->setModel(courseIdModel);
}
void MainWindow::setTypeIdModel()
{
    typeIdModel->setQuery("select typ_ID from tbl_type");
    ui->typeIDComBox->setModel(typeIdModel);
}

//设置用户名
void MainWindow::setUserName(QString name)
{
    userName = name;
    if(name==""){
        ui->userQuitLoginBtn->setText("未登录");
        userGrade=10;
    }else{
        ui->userQuitLoginBtn->setText(name);
        //查找权限
        QSqlQuery q;
        q.exec(QString("select ugrade from tbl_users where uname='%1'").arg(userName));
        if(q.next()){
            userGrade=q.value(0).toInt();
        }else{
            userGrade=10;
        }
    }
    setRight(userGrade);
}

//退出登录及登录
void MainWindow::on_userQuitLoginBtn_clicked()
{
    setUserName("");
    setVisible(false);
    LoginDialog ldg;
    if(ldg.exec()==QDialog::Accepted){
        ui->stackedWidget->setCurrentIndex(0);
        ui->selTableComBox->setCurrentIndex(0);
        setVisible(true);
        setUserName(ldg.getUsetName());
    }else{
        close();
    }
}

//设置对应权限的功能
void MainWindow::setRight(int grade)
{
    if(grade<=1){
        ui->insertBtn->setEnabled(true);
        ui->insertBtn->setVisible(true);
        ui->delBtn->setEnabled(true);
        ui->delBtn->setVisible(true);
        ui->updateBtn->setEnabled(true);
        ui->updateBtn->setVisible(true);
    }else if(grade<=5){
        ui->insertBtn->setEnabled(false);
        ui->insertBtn->setVisible(false);
        ui->delBtn->setEnabled(false);
        ui->delBtn->setVisible(false);
        ui->updateBtn->setEnabled(true);
        ui->updateBtn->setVisible(true);
    }else{
        ui->insertBtn->setEnabled(false);
        ui->insertBtn->setVisible(false);
        ui->delBtn->setEnabled(false);
        ui->delBtn->setVisible(false);
        ui->updateBtn->setEnabled(false);
        ui->updateBtn->setVisible(false);
    }
}

//修改密码
void MainWindow::showNewPwdInputBox()
{
    QString newPwd = QInputDialog::getText(this,"修改密码","请输入您的新密码：");
    if(newPwd!=NULL)
    {
        QSqlQuery q;
        if(q.exec(QString("exec p_updateUser '%1','%2'").arg(userName).arg(newPwd))){
            QMessageBox::information(this,"消息","您已成功修改您的密码为："+newPwd+"\n请重新登录");
            ui->userQuitLoginBtn->click();  //退出
        }else{
            QMessageBox::critical(this,"错误",q.lastError().text(),QMessageBox::Ok);
        }
    }else{
        QMessageBox::information(this,"消息","未修改密码");
    }
}
