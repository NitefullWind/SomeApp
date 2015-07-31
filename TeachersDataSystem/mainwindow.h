#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

class QSqlTableModel;
class QSqlQuery;
class QSqlQueryModel;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void setUserName(QString name);

private slots:
    void on_selTableComBox_currentIndexChanged(const QString &text);

    void on_selClassComBox_currentIndexChanged(const QString &text);

    void on_selTeachComBox_currentIndexChanged(const QString &text);

    void on_selTypeComboBox_currentIndexChanged(const QString &text);

    void on_selectBtn_clicked();

    void on_delBtn_clicked();

    void on_insertBtn_clicked();

    void on_updateBtn_clicked();

//    void on_teachIDComBox_currentIndexChanged(const QString &text);

    void on_typeIDComBox_currentIndexChanged(const QString &text);

    void on_manageSureBtn_clicked();

    void on_classTeachIDComBox_currentIndexChanged(const QString &text);

    void on_courseTeachIDComBox_currentIndexChanged(const QString &text);

    void on_courseClassIDComBox_currentIndexChanged(const QString &text);

    void on_courseIDComBox_currentIndexChanged(const QString &text);

    void on_userQuitLoginBtn_clicked();

    void showNewPwdInputBox();

    void on_selDateComBox_currentIndexChanged(const QString &text);

    void on_freshBtn_clicked();

private:
    Ui::MainWindow *ui;
    QString userName, tableName;
    int userGrade;
    void setRight(int grade);
    QSqlTableModel *model;
    QSqlQueryModel *queryModel,*teacherIdModel,*classIdModel, *courseIdModel, *typeIdModel;
    void setTeacherIdModel();
    void setClassIdModel();
    void setCourseIdModel();
    void setTypeIdModel();
    void updateModel();
    QSqlQuery *query;
    bool isNewRecord;   //代表是插入还是更新数据
    QString getTableName();
    QString id;

    void setToolBoxElsePageNotEnabled(int index);
};

#endif // MAINWINDOW_H
