﻿#ifndef ORDER_H
#define ORDER_H

#include <QWidget>

#include "Myinclude/DrawItem.h"
#include "Myinclude/sql_connect.h"
#include "user_center.h"
#include "Myinclude/pay.h"
#include "Form/manage.h"
#include <QStandardItem>
#include <QStandardItemModel>
#include <QModelIndex>
#include <QDialog>
#include <QButtonGroup>
#include <QObjectUserData>
#include <QSortFilterProxyModel>
#include <QMenu>
#include <QAction>


namespace Ui {
class order;
}

class order : public QWidget
{
    Q_OBJECT

public:
    explicit order(QWidget *parent = nullptr);
    ~order();
    void setuc(user_center * u);
    void setpys(pay * p);
    void setmanage(Manage * m);
    void user(QString str,int vip);

//private:
//    Ui::order *ui;
//    QListView *listView;
//    QStandardItemModel *standardItemModel;
//private slots:
//    void itemClicked(QModelIndex index);
//};

private slots:
//    void onButtonClicked(QAbstractButton *button);

    void search();

    void itemClicked(QModelIndex modelIndex);
    void on_allBtn_clicked();
    void on_riceBtn_clicked();
    void on_noodleBtn_clicked();
    void on_soupBtn_clicked();
    void on_snackBtn_clicked();
    void on_drinkBtn_clicked();
    void on_fireBtn_clicked();

    //void on_setRedBtn_clicked();
    void on_verifyBtn_clicked();
    void on_orderBtn_toggled(bool checked);
    void on_checkBtn_clicked();  
    void on_clearBtn_clicked();
    void on_deleteBtn_clicked();

    void orderShow();
    void orderFresh();
    void userCenter_selected();
    void quit_selected();


private:
    Ui::order *ui;
    QButtonGroup *m_filterButtonGroup;
    ItemDelegate *m_delegate;                 //委托
    QSortFilterProxyModel* m_proxyModel;
    QStandardItemModel *m_model;
    QMenu *m_menu;
    QAction *m_userCenter,*m_quit;

    user_center *uc;
    pay * pys;
    Manage * manag;

    int totalNum;
    int riceNum;
    int noodleNum;
    int soupNum;
    int snackNum;
    int drinkNum;
    int fireNum;
    int selectNum;
    double totalPrice;
    QString userName;
    int vipLevel;
    double discountPrice;

    void initData();
    void updateButtonNum();

signals:
    void quit();
    void ucShow();
    void ucFresh();

};


#endif // ORDER_H
