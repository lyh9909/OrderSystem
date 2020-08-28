#include "user_center.h"
#include "ui_user_center.h"

#pragma execution_character_set("utf-8")  //解决中文乱码问题

user_center::user_center(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::user_center)
{
    ui->setupUi(this);

    m_model = new QStandardItemModel();


    ui->listView->setModel(m_model);
    ui->listView->setEditTriggers(QAbstractItemView:: NoEditTriggers);
        //connect(ui->listView,SIGNAL(clicked(QModelIndex)),this,SLOT(itemClicked(QModelIndex)));

}

user_center::~user_center()
{
    delete ui;
}

void user_center::setAll(QModelIndexList modelIndexList)
{
    QStringList strList;
    strList.append("");
    strList.append("");
    strList.append("订单编号");
    for (QModelIndex modelIndex : modelIndexList)
    {
        QVariant variant = modelIndex.data(Qt::UserRole+2);
        ItemiData data = variant.value<ItemiData>();

        strList.append(tr("%1").arg(data.name));

    }
    int nCount = strList.size();

    for (int i = 0; i < nCount; i++)
    {
        QString string = static_cast<QString>(strList.at(i));
        QStandardItem *item = new QStandardItem(string);
        m_model->appendRow(item);

    }
}

void user_center::ucShow()
{//显示即时订单
    this->show();
    ui->payBtn->show();
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
