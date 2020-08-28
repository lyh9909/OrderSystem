﻿#include "user_center.h"
#include "ui_user_center.h"

#pragma execution_character_set("utf-8")  //解决中文乱码问题

user_center::user_center(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::user_center)
{
    ui->setupUi(this);

    m_model = new QStandardItemModel();
    QStringList strList;
    strList.append("");
    strList.append("");
    strList.append("");

    int nCount = strList.size();

    for (int i = 0; i < nCount; i++)
    {
        QString string = static_cast<QString>(strList.at(i));
        QStandardItem *item = new QStandardItem(string);
        m_model->appendRow(item);

    }
    ui->listView->setModel(m_model);
    ui->listView->setEditTriggers(QAbstractItemView:: NoEditTriggers);
        //connect(ui->listView,SIGNAL(clicked(QModelIndex)),this,SLOT(itemClicked(QModelIndex)));

}

user_center::~user_center()
{
    delete ui;
}

void user_center::settotal(double price)
{
    ui->totalPrice->setText(tr("合计 ¥:%1").arg(QString::number(price,'f',2)));
}

void user_center::ucShow()
{//显示即时订单
    this->show();
    ui->totalPrice->show();
    ui->payBtn->show();
}

void user_center::ucOrder()
{//显示既往订单
    this->show();
    ui->totalPrice->hide();
    ui->payBtn->hide();
}

void user_center::on_returnBtn_clicked()
{
    this->close();
    emit ret();
}

void user_center::on_payBtn_clicked()
{
    this->close();
    emit payShow();
}