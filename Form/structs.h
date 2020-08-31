#ifndef STRUCTS_H
#define STRUCTS_H

#include <QPixmap>
#include <QMetaType>

struct DishItemData{
    QString Dishtype;
    QString Dishname;
    QPixmap Dishphoto;
    double Dishprice;
};

Q_DECLARE_METATYPE(DishItemData)

struct OrderItemData{
    QString ordernumber;
    QString orderuser;
    double orderprice;
    QString ordercontent;
};

Q_DECLARE_METATYPE(OrderItemData)

struct UserItemData{
    QString username;
    QString userpassword;
    QString uservip;
};

Q_DECLARE_METATYPE(UserItemData)

struct SellItemData{
    QString dishname;
    int sells;
};

Q_DECLARE_METATYPE(SellItemData)

#endif // STRUCTS_H
