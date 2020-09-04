#ifndef DRAWITEM_H
#define DRAWITEM_H

#include <QStyledItemDelegate>
#include <QModelIndex>
#include <QStandardItemModel>
#include <QPainter>
#include <QStyle>
#include <QEvent>
#include <QDebug>
#include <QMetaType>
#include "sql_connect.h"


class ItemStyleDesigner : public QStyledItemDelegate
{
    Q_OBJECT
signals:

public:
    explicit ItemStyleDesigner(QObject *parent = 0);
    ~ItemStyleDesigner();


    void paint(QPainter * painter,const QStyleOptionViewItem & option,const QModelIndex & index) const;
    QSize sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const;

private:


};

class ItemOrderDesigner : public QStyledItemDelegate
{
    Q_OBJECT
signals:

public:
    explicit ItemOrderDesigner(QObject *parent = 0);
    ~ItemOrderDesigner();


    void paint(QPainter * painter,const QStyleOptionViewItem & option,const QModelIndex & index) const;
    QSize sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const;

private:


};

class ItemStatiusDesigner : public QStyledItemDelegate
{
    Q_OBJECT
signals:

public:
    explicit ItemStatiusDesigner(QObject *parent = 0);
    ~ItemStatiusDesigner();


    void paint(QPainter * painter,const QStyleOptionViewItem & option,const QModelIndex & index) const;
    QSize sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const;

private:


};

class ItemDelegate : public QStyledItemDelegate
{
    Q_OBJECT
signals:

public:
    explicit ItemDelegate(QObject *parent = 0);
    ~ItemDelegate();

    //重写重画函数
    void paint(QPainter * painter,const QStyleOptionViewItem & option,const QModelIndex & index) const;
    QSize sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const;


private:

};

struct ItemOrderData{
    QString onumber;
    QString ouser;
    QString totalprice;
    QString content;
    QString mark;
};

Q_DECLARE_METATYPE(ItemOrderData)

struct ItemData{
    QString number;
    QString name;
    QString price;
    QString num;
    //QString sell;
};

Q_DECLARE_METATYPE(ItemData)

struct ItemStatiusData
{
    QString name;
    QString counts;
};

Q_DECLARE_METATYPE(ItemStatiusData)

typedef enum{
    rice,
    noodle,
    soup,
    snack,
    drink,
    fire,
} ItemStatus;

typedef enum{
    Select,
    None,
}ItemSelect;

struct ItemiData{
    QString name;
    double price;
    int num;
    QPixmap img;
};

Q_DECLARE_METATYPE(ItemiData)

#endif // DRAWITEM_H
