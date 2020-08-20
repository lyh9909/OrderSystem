#include "order.h"
#include "ui_order.h"

#include <QBrush>
#include <QRadialGradient>
#include <QDebug>


order::order(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::order)
{
    ui->setupUi(this);

//    listView = new QListView(this);
//    standardItemModel = new QStandardItemModel(this);

//    QStringList strList;
//    strList.append("string1");
//    strList.append("string2");
//    strList << "string3";
//    strList += "string4";
//    int nCount = strList.size();

//    for (int i = 0; i < nCount; i++)
//    {
//        QString string = static_cast<QString>(strList.at(i));
//        QStandardItem *item = new QStandardItem(string);
//        standardItemModel->appendRow(item);

//    }
//    listView->setModel(standardItemModel);
//    listView->setFixedSize(800,600);
//    connect(listView,SIGNAL(clicked(QModelIndex)),this,SLOT(itemClicked(QModelIndex)));




    initData();
    updateButtonNum();

    ui->searchBtn->setCursor(Qt::PointingHandCursor);

    m_delegate = new ItemDelegate(this);
    m_filterButtonGroup = new QButtonGroup(this);

    // 设置互斥
    m_filterButtonGroup->setExclusive(true);

    m_filterButtonGroup->addButton(ui->allBtn);
    m_filterButtonGroup->addButton(ui->redBtn);
    m_filterButtonGroup->addButton(ui->blueBtn);
    m_filterButtonGroup->addButton(ui->yellowBtn);

    // 连接信号槽
//    connect(m_filterButtonGroup, SIGNAL(buttonClicked(QAbstractButton*)), this, SLOT(onButtonClicked(QAbstractButton*)));
    connect(ui->listView,SIGNAL(clicked(QModelIndex)),this,SLOT(itemClicked(QModelIndex)));
    connect(ui->searchBtn, SIGNAL(clicked(bool)), this, SLOT(search()));

    ui->listView->setItemDelegate(m_delegate);       //为视图设置委托
    ui->listView->setSpacing(35);                   //为视图设置控件间距

    m_proxyModel = new QSortFilterProxyModel(ui->listView);
    m_proxyModel->setSourceModel(m_model);
    m_proxyModel->setFilterRole(Qt::UserRole);
    m_proxyModel->setDynamicSortFilter(true);

    ui->listView->setModel(m_proxyModel);                  //为委托设置模型
    ui->listView->setViewMode(QListView::IconMode); //设置Item图标显示
    ui->listView->setDragEnabled(false);            //控件不允许拖动

    ui->spinNum->setRange(0,50);


}

order::~order()
{
    delete ui;
}


void order::initData()
{ // 数据初始化
    totalNum = 50;
    redNum = 0;
    blueNum = 0;
    yellowNum = 0;
    selectNum = 0;
    totalPrice = 0;

    m_model = new QStandardItemModel();
    ConnectSQLODBC db("QODBC", "localhost", "Test", "", "");
    UseODBCDataBase * uodbc = new UseODBCDataBase(db.GetSqlDatabase());
    QVector<QVector<QString> > res = uodbc->ExecGetAllData("Dishs", 5);
    for (int i = 0; i < res.size(); ++i) {
        QStandardItem *Item = new QStandardItem;

        ItemiData itemData;

        itemData.name = res[i][2];
        itemData.price = res[i][3].toDouble();
        itemData.num = res[i][4].toInt();

        int randNum = rand()% 3;
        ItemStatus itemStatus;

        switch (randNum) {
        case 0:
            itemStatus = S_RED;
            redNum++;
            break;
        case 1:
            itemStatus = S_BLUE;
            blueNum++;
            break;
        case 2:
            itemStatus = S_YELLOW;
            yellowNum++;
            break;
        default:
            break;
        }


        ItemSelect itemSelect;
        itemSelect = None;


        Item->setData(itemStatus,Qt::UserRole);  // itemStatus数据储存
        Item->setData(itemSelect,Qt::UserRole+1);  // itemSelect数据储存
        Item->setData(QVariant::fromValue(itemData),Qt::UserRole+2);//结构体数据储存
        Item->setData(itemData.name,Qt::UserRole+3);

        m_model->appendRow(Item);      //追加Item
//        m_model->removeRow(Index.row());      //移除Item


    }
}

void order::updateButtonNum()
{
    ui->allBtn->setText(tr("All %1").arg(totalNum));
    ui->redBtn->setText(tr("Rice %1").arg(redNum));
    ui->blueBtn->setText(tr("Noodle %1").arg(blueNum));
    ui->yellowBtn->setText(tr("FireDish %1").arg(yellowNum));
    ui->orderBtn->setText(tr("已点 %1").arg(selectNum));
    ui->checkBtn->setText(tr("确认订单 ¥:%1").arg(totalPrice));
}

//void order::onButtonClicked(QAbstractButton *button)
//{// 点击button

//    qDebug() << button->text();

//}

void order::search()
{
    QString strText = ui->searchEdit->text();
    if (!strText.isEmpty())
    {
        qDebug() << "search";
        m_proxyModel->setFilterRole(Qt::UserRole+3);
        if(m_proxyModel)
        {

            m_proxyModel->setFilterFixedString(QString(strText));
        }
    }
}

void order::itemClicked(QModelIndex modelIndex)
{// 点击特定item

    ui->spinNum->valueChanged(1);

    QModelIndexList sourceIndexList;
    sourceIndexList<<m_proxyModel->mapToSource(modelIndex); //获取源model的modelIndex

    for (QModelIndex sourceIndex : sourceIndexList){

        ItemSelect selectStatus = (ItemSelect)(sourceIndex.data(Qt::UserRole+1).toInt());

        QVariant variant = sourceIndex.data(Qt::UserRole+2);
        ItemiData data = variant.value<ItemiData>();

        switch (selectStatus) {
            case Select:
                ui->spinNum->setValue(data.num);
                break;
            case None:
                selectStatus = Select;
                selectNum++;
                ui->spinNum->setValue(1);
                data.num = ui->spinNum->value();
                totalPrice += data.price * data.num;
                break;

        }


        m_model->setData(sourceIndex,selectStatus,Qt::UserRole+1);
        m_model->setData(sourceIndex,QVariant::fromValue(data),Qt::UserRole+2);
    }
    updateButtonNum();
}


void order::on_allBtn_clicked()
{// 点击allBtn

    m_proxyModel->setFilterRole(Qt::UserRole);
    if(m_proxyModel)
    {
        m_proxyModel->setFilterFixedString(QString());
    }
}

void order::on_redBtn_clicked()
{// 点击redBtn

    m_proxyModel->setFilterRole(Qt::UserRole);
    if(m_proxyModel)
    {
        m_proxyModel->setFilterFixedString(QString::number(S_RED));
    }
}

void order::on_blueBtn_clicked()
{// 点击blueBtn

    m_proxyModel->setFilterRole(Qt::UserRole);
    if(m_proxyModel)
    {
        m_proxyModel->setFilterFixedString(QString::number(S_BLUE));
    }
}

void order::on_yellowBtn_clicked()
{// 点击yellowBtn

    m_proxyModel->setFilterRole(Qt::UserRole);
    if(m_proxyModel)
    {
        m_proxyModel->setFilterFixedString(QString::number(S_YELLOW));
    }
}


//void order::on_setRedBtn_clicked()
//{
//    QModelIndexList modelIndexList = ui->listView->selectionModel()->selectedIndexes();
//    QModelIndexList sourceIndexList;
//    for (QModelIndex modelIndex : modelIndexList){
//        sourceIndexList<<m_proxyModel->mapToSource(modelIndex); //获取源model的modelIndex
//    }

////    g_proxyModel->setDynamicSortFilter(false);
//    for (QModelIndex sourceIndex : sourceIndexList){
//        ItemStatus status = (ItemStatus)(sourceIndex.data(Qt::UserRole).toInt());  //获取单一数据
//        qDebug() << "Index : " << sourceIndex.row();

//        switch (status) {
//            case S_RED:
//                redNum--;
//                break;
//            case S_BLUE:
//                blueNum--;
//                break;
//            case S_YELLOW:
//                yellowNum--;
//                break;
//        }

//        status = S_RED;
//        redNum++;

//        m_model->setData(sourceIndex,status,Qt::UserRole);
//    }
////    g_proxyModel->setDynamicSortFilter(true);
//    updateButtonNum();
//}

void order::on_verifyBtn_clicked()
{
    QModelIndexList modelIndexList = ui->listView->selectionModel()->selectedIndexes();
    QModelIndexList sourceIndexList;
    for (QModelIndex modelIndex : modelIndexList){
        sourceIndexList<<m_proxyModel->mapToSource(modelIndex); //获取源model的modelIndex
    }

    for (QModelIndex sourceIndex : sourceIndexList){

        ItemSelect selectStatus = (ItemSelect)(sourceIndex.data(Qt::UserRole+1).toInt());

        QVariant variant = sourceIndex.data(Qt::UserRole+2);
        ItemiData data = variant.value<ItemiData>();

        int dataPreNum = data.num;
        data.num = ui->spinNum->value();
        if(!data.num)
        {
            selectStatus = None;
            selectNum--;
            totalPrice -= data.price * dataPreNum;
        }
        else
        {
            selectStatus = Select;
            totalPrice += data.price * (data.num - dataPreNum);
        }

        m_model->setData(sourceIndex,selectStatus,Qt::UserRole+1);
        m_model->setData(sourceIndex,QVariant::fromValue(data),Qt::UserRole+2);
    }
    updateButtonNum();
}

void order::on_orderBtn_clicked()
{// 点击orderBtn

    m_proxyModel->setFilterRole(Qt::UserRole+1);
    if(m_proxyModel)
    {
        m_proxyModel->setFilterFixedString(QString::number(Select));
    }
}

void order::on_checkBtn_clicked()
{// 点击checkBtn
    this->close();
    pys->settotal(totalPrice);
    emit payShow();
}

void order::orderShow()
{
    this->show();
}

void order::setpys(pay * p)
{
    pys = p;
}
