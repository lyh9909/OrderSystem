#include "pay.h"
#include "ui_pay.h"

pay::pay(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::pay)
{
    ui->setupUi(this);
}

pay::~pay()
{
    delete ui;
}

void pay::settotal(double price)
{
    ui->payPrice->setText(QString::number(price,'f',2));
}


void pay::on_payBtn_clicked()
{
    emit orderFresh();
    this->close();
}
void pay::on_laterBtn_clicked()
{
    emit orderFresh();
    this->close();
}

void pay::payShow()
{
    this->show();
}

