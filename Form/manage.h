#ifndef MANAGE_H
#define MANAGE_H

#include <QMainWindow>
#include <QStandardItem>
#include <QStandardItemModel>
#include <QModelIndex>
#include <QObjectUserData>
#include <QSortFilterProxyModel>
#include <QSpinBox>
#include <QStringListModel>
#include <QFormLayout>
#include <QLabel>
#include <QLineEdit>
#include <QDialogButtonBox>
#include "Myinclude/DrawItem.h"

namespace Ui {
class Manage;
}

class Manage : public QMainWindow
{
    Q_OBJECT

public:
    explicit Manage(QWidget *parent = nullptr);
    ~Manage();
    void InitModel();   //初始化界面列表
    void connectsql();      //连接数据库
    void getdishes(QVector<ItemData> & ida, QVector<QString> & types);    //获取菜品
    QListView * gettype(int n = -1);    //获取类型对象窗口
    QString gettypename();      //获取类型名称
    int gettypenum(QString & q);    //获取字符串对应的数字
    void InitOrderModel();   //初始化订单界面
    void getorders(QVector<ItemOrderData> & ida);   //获取订单信息
    void InitStatiusModel();   //初始化订单界面
    void getstatius(QVector<ItemStatiusData> & ida, int n);   //获取统计信息
    QListView * getstatiustype(int n);

private slots:
    void on_Add_dish_clicked();     //添加菜品
    void itemClicked(QModelIndex index);    //...
    void on_DishsSelect_currentChanged(int index);      //菜单栏选项切换
    void on_Change_dish_clicked();      //修改菜品
    void on_Delete_dish_clicked();      //删除菜品

    void on_Change_Order_clicked();

    void on_Delete_Order_clicked();

    void manageShow();

private:
    Ui::Manage *ui;
    QVector<QStandardItemModel *> ItemModel;      //自定义Item管理
    ItemStyleDesigner * ItemDesigner;   //自定义样式
    QVector<QSortFilterProxyModel *> myProxy;    //代理
    UseODBCDataBase * uodbc;    //执行数据库操作
    QVector<QString> colnames;  //存储数据库列名
    QVector<QString> ordercolnames;  //存储数据库列名
    QStandardItemModel * OrderItemModel;        //自定义订单卡片
    QSortFilterProxyModel * OrdermyProxy;       //代理
    ItemOrderDesigner * OrderItemDesigner;   //自定义样式
    QVector<QStandardItemModel *> StatiusItemModel;
    QVector<QSortFilterProxyModel *> StatiusmyProxy;
    ItemStatiusDesigner * StatiusDesigner;

signals:


};

#endif // MANAGE_H
