#include "user_center.h"
#include "ui_user_center.h"

#define DISCOUNT 0.12

#pragma execution_character_set("utf-8")  //解决中文乱码问题

user_center::user_center(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::user_center)
{
    ui->setupUi(this);

    m_model = new QStandardItemModel();

    ui->listView->setModel(m_model);
    ui->listView->setEditTriggers(QAbstractItemView:: NoEditTriggers);
//    connect(ui->listView,SIGNAL(clicked(QModelIndex)),this,SLOT(itemClicked(QModelIndex)));

}

user_center::~user_center()
{
    delete ui;
}


void user_center::setAll(QModelIndexList modelIndexList, bool vipFlag)
{
    totalPrice = 0;
    discountPrice = 0;

    m_model->removeRows(0,m_model->rowCount());

    QDateTime curDateTime=QDateTime::currentDateTime();

    QStringList strList;
    strList.append("");
    strList.append("");
    strList.append("-------------------------------");
    strList.append(tr("下单时间：%1").arg(curDateTime.toString("yyyy-MM-dd hh:mm:ss")));
    strList.append(tr("下单桌号：%1").arg(curDateTime.toString("yyyyMMdd")));
    strList.append("-------------------------------");

    for (QModelIndex modelIndex : modelIndexList)
    {
        QVariant variant = modelIndex.data(Qt::UserRole+2);
        ItemiData data = variant.value<ItemiData>();

        strList.append(tr("%1 ").arg(data.name));
        strList.append(tr("     ×%1     ￥%2").arg(data.num).arg(data.price*data.num));
        totalPrice += data.price * data.num;

    }
    strList.append("-------------------------------");
    strList.append(tr("合计：￥%1").arg(QString::number(totalPrice,'f',2)));
    if(vipFlag == true)
    {
        discountPrice = DISCOUNT * totalPrice;
        strList.append(tr("优惠：-￥%1").arg(QString::number(discountPrice,'f',2)));
    }
    strList.append(tr("应付：￥%1").arg(QString::number(totalPrice - discountPrice,'f',2)));

    for (int i = 0; i < strList.size(); i++)
    {
        QString string = static_cast<QString>(strList.at(i));
        QStandardItem *item = new QStandardItem(string);
        //item->setTextAlignment(Qt::AlignCenter);
        m_model->appendRow(item);

    }
}

void user_center::ucShow()
{//显示即时订单
    this->show();

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
