#include "user_center.h"
#include "ui_user_center.h"

#define DISCOUNT1 0.05
#define DISCOUNT2 0.1
#define DISCOUNT3 0.15

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


void user_center::setAll(QModelIndexList modelIndexList,QString user, int vipLevel)
{
    m_modelIndexList = modelIndexList;
    userName = user;
    vip = vipLevel;
    totalPrice = 0;
    discountPrice = 0;

    m_model->removeRows(0,m_model->rowCount());

    curDateTime = QDateTime::currentDateTime();

    QStringList strList;
    strList.append("");
    strList.append("");
    strList.append("-------------------------------");
    strList.append(tr("下单时间：%1").arg(curDateTime.toString("yyyy-MM-dd hh:mm:ss")));
    strList.append(tr("下单编号：%1").arg(curDateTime.toString("yyyyMMddhhmmss")));
    strList.append("-------------------------------");

    for (QModelIndex modelIndex : modelIndexList)
    {
        QVariant variant = modelIndex.data(Qt::UserRole+2);
        ItemiData data = variant.value<ItemiData>();

        strList.append(tr("%1 ").arg(data.name));
        strList.append(tr("     ×%1     ￥%2").arg(data.num).arg(data.price*data.num));
        totalPrice += data.price * data.num;
        orderContent += data.name + "*"+QString::number(data.num) + " ";

    }
    strList.append("-------------------------------");
    strList.append(tr("合计：￥%1").arg(QString::number(totalPrice,'f',2)));
    if(vip)
    {
        switch (vip) {
        case 1:
            discountPrice = DISCOUNT1 * totalPrice;
            break;
        case 2:
            discountPrice = DISCOUNT2 * totalPrice;
            break;
        default:
            discountPrice = DISCOUNT3 * totalPrice;
            break;
        }
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
    QVector<QString> temp;  //存储修改后的数据
    temp.push_back(curDateTime.toString("yyyyMMddhhmmss"));
    temp.push_back(userName);
    temp.push_back(QString::number(totalPrice - discountPrice));
    temp.push_back(orderContent);
    temp.push_back(ui->orderMark->toPlainText());
    ConnectSQLODBC db("QODBC", "localhost", "Test", "", "");
    db.OpenDataBase();
    uodbc = new UseODBCDataBase(db.GetSqlDatabase());

    uodbc->ExecInsertData("Orders", temp);       //插入新数据

    emit payShow();
}
