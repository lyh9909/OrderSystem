#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
}

Widget::~Widget()
{
    delete ui;
}


void Widget::on_Button_SignIn_Manager_clicked()
{
    emit loginManageShow();
    this->hide();
}

void Widget::on_Button_SignIn_Customer_clicked()
{
    emit loginShow();
    this->hide();
}

