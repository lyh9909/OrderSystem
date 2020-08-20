#include "widget.h"
#include "login.h"
#include "Form/manage.h"
#include "Form/login_manage.h"
#include "Myinclude/order.h"

#include <QApplication>
#include <iostream>
#include <QObject>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    Widget w;
    login l;
    login_manage l_m;
    Manage m;
    order o;
    pay p;

    QObject::connect(&w,SIGNAL(loginShow()),&l,SLOT(loginShow()));
    QObject::connect(&w,SIGNAL(loginManageShow()),&l_m,SLOT(loginManageShow()));
    QObject::connect(&l,SIGNAL(orderShow()),&o,SLOT(orderShow()));
    QObject::connect(&l_m,SIGNAL(manageShow()),&m,SLOT(manageShow()));
    QObject::connect(&o,SIGNAL(payShow()),&p,SLOT(payShow()));
    QObject::connect(&p,SIGNAL(orderShow()),&o,SLOT(orderShow()));

    o.setpys(&p);

    w.show();

    return a.exec();
}
