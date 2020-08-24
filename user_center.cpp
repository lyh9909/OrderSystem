#include "user_center.h"
#include "ui_user_center.h"

user_center::user_center(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::user_center)
{
    ui->setupUi(this);
}

user_center::~user_center()
{
    delete ui;
}


void user_center::ucShow()
{
    this->show();
}

void user_center::on_quitBtn_clicked()
{
    this->close();
    emit quit();
}
