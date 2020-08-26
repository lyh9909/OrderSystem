#ifndef PAY_H
#define PAY_H

#include <QDialog>
#include <QFormLayout>
#include <QLabel>
#include <QDebug>
#include <QWidget>
#include <QFileDialog>
#include "sql_connect.h"

namespace Ui {
class pay;
}

class pay : public QWidget
{
    Q_OBJECT

public:
    explicit pay(QWidget *parent = nullptr);
    ~pay();
    void settotal(double price);

private slots:
    void on_payBtn_clicked();

    void on_cancelBtn_clicked();

    void payShow();

private:
    Ui::pay *ui;
    UseODBCDataBase * uodbc;    //执行数据库操作

protected:


signals:
    void ucShow();
};

#endif // PAY_H
