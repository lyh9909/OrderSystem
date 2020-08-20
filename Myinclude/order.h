#ifndef ORDER_H
#define ORDER_H

#include <QWidget>

#include "Myinclude/DrawItem.h"
#include "Myinclude/sql_connect.h"
#include "Myinclude/pay.h"
#include <QStandardItem>
#include <QStandardItemModel>
#include <QModelIndex>
#include <QDialog>
#include <QButtonGroup>
#include <QObjectUserData>
#include <QSortFilterProxyModel>

namespace Ui {
class order;
}

class order : public QWidget
{
    Q_OBJECT

public:
    explicit order(QWidget *parent = nullptr);
    ~order();
    void setpys(pay * p);

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
    void on_redBtn_clicked();
    void on_allBtn_clicked();
    void on_blueBtn_clicked();
    void on_yellowBtn_clicked();

    //void on_setRedBtn_clicked();
    void on_verifyBtn_clicked();
    void on_orderBtn_clicked();
    void on_checkBtn_clicked();

    void orderShow();

private:
    Ui::order *ui;
    QButtonGroup *m_filterButtonGroup;
    ItemDelegate *m_delegate;                 //委托
    QSortFilterProxyModel* m_proxyModel;
    QSortFilterProxyModel* m_selectModel;
    QStandardItemModel *m_model;
    pay * pys;

    int totalNum;
    int redNum;
    int blueNum;
    int yellowNum;
    int selectNum;
    double totalPrice;

    void initData();
    void updateButtonNum();

signals:
    void payShow();

};


#endif // ORDER_H
