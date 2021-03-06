﻿#include "widget.h"
#include "login.h"
#include "Form/manage.h"
#include "Form/login_manage.h"
#include "Myinclude/order.h"
#include "user_center.h"

#include <QApplication>
#include <iostream>
#include <QObject>

#pragma execution_character_set("utf-8")  //解决中文乱码问题

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    Widget w;
    login l;
    //login_manage l_m;
    //Manage m;
    order o;
    pay p;
    user_center uc;
    o.setWindowTitle("点餐系统");
    p.setWindowTitle("订单支付");
    uc.setWindowTitle("我的订单");


    QObject::connect(&w,SIGNAL(loginShow()),&l,SLOT(loginShow()));
    //QObject::connect(&w,SIGNAL(loginManageShow()),&l_m,SLOT(loginManageShow()));
    QObject::connect(&l,SIGNAL(orderShow()),&o,SLOT(orderFresh()));
    //QObject::connect(&l_m,SIGNAL(manageShow()),&m,SLOT(manageShow()));
    QObject::connect(&o,SIGNAL(quit()),&l,SLOT(loginShow()));
    QObject::connect(&o,SIGNAL(ucShow()),&uc,SLOT(ucShow()));
    QObject::connect(&o,SIGNAL(ucFresh()),&uc,SLOT(ucFresh()));
    QObject::connect(&uc,SIGNAL(ret()),&o,SLOT(orderShow()));
    QObject::connect(&uc,SIGNAL(payShow()),&p,SLOT(payShow()));
    QObject::connect(&p,SIGNAL(orderFresh()),&o,SLOT(orderFresh()));

    o.setuc(&uc);
    o.setpys(&p);
    //o.setmanage(&m);
    l.setOrder(&o);

    w.show();

    return a.exec();
}
