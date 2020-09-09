#ifndef USER_CENTER_H
#define USER_CENTER_H

#include <QWidget>
#include "Myinclude/DrawItem.h"
#include "Myinclude/sql_connect.h"
#include <QStandardItem>
#include <QStandardItemModel>
#include <QModelIndex>

#include <QTcpSocket>
#include <QTcpServer>
#include <QHostAddress>
#include <QHostInfo>

#include <QTimer>

namespace Ui {
class user_center;
}

class user_center : public QWidget
{
    Q_OBJECT

public:
    explicit user_center(QWidget *parent = nullptr);
    ~user_center();

    void connectsql();      //连接数据库
    void setAll(QModelIndexList modelIndexList,QString user,int vipLevel,QString table,int person);

signals:
    void ret();
    void payShow();

private:
    Ui::user_center *ui;
    QTcpSocket * qsocket;
    QStandardItemModel *m_model;
    ItemDelegate *m_delegate;
    QModelIndexList m_modelIndexList;
    QVector<QString> colnames;
    QDateTime curDateTime;
    QString orderContent;
    QString userName;
    int vip;
    UseODBCDataBase * uodbc;

    double totalPrice;
    double discountPrice;
    int orderNum;
    QString tableUse;
    QString orderList;
    int orderperson;

    QTimer *fTimer; //定时器


private slots:
    void ucShow();
    void ucFresh();
    void on_returnBtn_clicked();
    void on_payBtn_clicked();
    void timerUpdate();

};

#endif // USER_CENTER_H
