QT       += core gui
QT       += sql
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    Form/login_manage.cpp \
    Form/manage.cpp \
    Myinclude/drawitem.cpp \
    Myinclude/login_w.cpp \
    Myinclude/sql_connect.cpp \
    Myinclude/order.cpp\
    Myinclude/pay.cpp\
    login.cpp \
    main.cpp \
    widget.cpp

HEADERS += \
    Form/login_manage.h \
    Form/manage.h \
    Myinclude/drawitem.h \
    Myinclude/login_w.h \
    Myinclude/sql_connect.h \
    Myinclude/order.h\
    Myinclude/pay.h\
    login.h \
    widget.h

FORMS += \
    Form/login_manage.ui \
    Form/manage.ui \
    Form/order.ui\
    Form/pay.ui\
    login.ui \
    widget.ui

TRANSLATIONS += \
    Order_zh_CN.ts

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    pictures.qrc