#include "order.h"
#include "ui_order.h"

#include <QBrush>
#include <QRadialGradient>
#include <QDebug>

#pragma execution_character_set("utf-8")  //解决中文乱码问题

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


    m_delegate = new ItemDelegate(this);
    m_filterButtonGroup = new QButtonGroup(this);

    // 设置互斥
    m_filterButtonGroup->setExclusive(true);

    m_filterButtonGroup->addButton(ui->allBtn);
    m_filterButtonGroup->addButton(ui->riceBtn);
    m_filterButtonGroup->addButton(ui->noodleBtn);
    m_filterButtonGroup->addButton(ui->soupBtn);
    m_filterButtonGroup->addButton(ui->snackBtn);
    m_filterButtonGroup->addButton(ui->drinkBtn);
    m_filterButtonGroup->addButton(ui->fireBtn);
    m_filterButtonGroup->addButton(ui->orderBtn);

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

    m_menu = new QMenu(ui->userBtn);
    m_userCenter = new QAction(m_menu);
    m_quit = new QAction(m_menu);
    m_userCenter->setText(QObject::tr("个人中心"));
    m_quit->setText(QObject::tr("退出系统"));
    m_menu->addAction(m_userCenter);
    m_menu->addAction(m_quit);
    ui->userBtn->setMenu(m_menu);
    connect(m_userCenter, &QAction::triggered, this,&order::userCenter_selected);
    connect(m_quit, &QAction::triggered, this,&order::quit_selected);


    ui->spinNum->setRange(0,50);


}

order::~order()
{
    delete ui;
}


void order::initData()
{ // 数据初始化
    riceNum = 0;
    noodleNum = 0;
    soupNum = 0;
    snackNum = 0;
    drinkNum = 0;
    fireNum = 0;
    selectNum = 0;
    totalPrice = 0;

    ui->clearBtn->hide();
    ui->clearLabel->hide();

    m_model = new QStandardItemModel();
    ConnectSQLODBC db("QODBC", "localhost", "Test", "", "");
    UseODBCDataBase * uodbc = new UseODBCDataBase(db.GetSqlDatabase());
    QVector<QVector<QString> > res = uodbc->ExecGetAllData("Dishs", 5);
    totalNum = res.size();
    for (int i = 0; i < res.size(); ++i) {
        QStandardItem *Item = new QStandardItem;

        ItemiData itemData;

        itemData.name = res[i][2];
        itemData.price = res[i][3].toDouble();
        itemData.num = 0;

        ItemStatus itemStatus;

        switch (manag->gettypenum(res[i][0])) {
        case 0:
            itemStatus = rice;
            riceNum++;
            break;
        case 1:
            itemStatus = noodle;
            noodleNum++;
            break;
        case 2:
            itemStatus = soup;
            soupNum++;
            break;
        case 3:
            itemStatus = snack;
            snackNum++;
            break;
        case 4:
            itemStatus = drink;
            drinkNum++;
            break;
        case 5:
            itemStatus = fire;
            fireNum++;
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
    ui->allBtn->setText(tr("All%1").arg(totalNum));
    ui->riceBtn->setText(tr("米饭%1").arg(riceNum));
    ui->noodleBtn->setText(tr("面条%1").arg(noodleNum));
    ui->soupBtn->setText(tr("汤%1").arg(soupNum));
    ui->snackBtn->setText(tr("零食%1").arg(snackNum));
    ui->drinkBtn->setText(tr("饮品%1").arg(drinkNum));
    ui->fireBtn->setText(tr("炒菜%1").arg(fireNum));
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

void order::on_riceBtn_clicked()
{// 点击riceBtn

    m_proxyModel->setFilterRole(Qt::UserRole);
    if(m_proxyModel)
    {
        m_proxyModel->setFilterFixedString(QString::number(rice));
    }
}

void order::on_noodleBtn_clicked()
{// 点击noodleBtn

    m_proxyModel->setFilterRole(Qt::UserRole);
    if(m_proxyModel)
    {
        m_proxyModel->setFilterFixedString(QString::number(noodle));
    }
}

void order::on_soupBtn_clicked()
{// 点击soupBtn

    m_proxyModel->setFilterRole(Qt::UserRole);
    if(m_proxyModel)
    {
        m_proxyModel->setFilterFixedString(QString::number(soup));
    }
}


void order::on_snackBtn_clicked()
{// 点击snackBtn

    m_proxyModel->setFilterRole(Qt::UserRole);
    if(m_proxyModel)
    {
        m_proxyModel->setFilterFixedString(QString::number(snack));
    }
}

void order::on_drinkBtn_clicked()
{// 点击drinkBtn

    m_proxyModel->setFilterRole(Qt::UserRole);
    if(m_proxyModel)
    {
        m_proxyModel->setFilterFixedString(QString::number(drink));
    }
}

void order::on_fireBtn_clicked()
{// 点击fireBtn

    m_proxyModel->setFilterRole(Qt::UserRole);
    if(m_proxyModel)
    {
        m_proxyModel->setFilterFixedString(QString::number(fire));
    }
}

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


void order::on_orderBtn_toggled(bool checked)
{
    if(checked == true)
    {
        ui->clearBtn->show();
        ui->clearLabel->show();
        m_proxyModel->setFilterRole(Qt::UserRole+1);
        if(m_proxyModel)
        {
            m_proxyModel->setFilterFixedString(QString::number(Select));
        }
    }
    else
    {
        ui->clearBtn->hide();
        ui->clearLabel->hide();

    }

}

void order::on_checkBtn_clicked()
{// 点击checkBtn
    this->close();
    pys->settotal(totalPrice);
    emit payShow();
}


void order::on_clearBtn_clicked()
{
    ui->listView->setSelectionMode(QAbstractItemView::ExtendedSelection);
    ui->listView->selectAll();

    QModelIndexList modelIndexList = ui->listView->selectionModel()->selectedIndexes();
    QModelIndexList sourceIndexList;
    for (QModelIndex modelIndex : modelIndexList){
        sourceIndexList<<m_proxyModel->mapToSource(modelIndex); //获取源model的modelIndex
    }

    for (QModelIndex sourceIndex : sourceIndexList){

        ItemSelect selectStatus = (ItemSelect)(sourceIndex.data(Qt::UserRole+1).toInt());

        QVariant variant = sourceIndex.data(Qt::UserRole+2);
        ItemiData data = variant.value<ItemiData>();

        data.num = 0;
        selectStatus = None;
        ui->spinNum->setValue(0);

        m_model->setData(sourceIndex,selectStatus,Qt::UserRole+1);
        m_model->setData(sourceIndex,QVariant::fromValue(data),Qt::UserRole+2);
    }
    selectNum = 0;
    totalPrice = 0;
    updateButtonNum();
    ui->listView->setSelectionMode(QAbstractItemView::SingleSelection);
}


void order::orderShow()
{
    this->show();
}

void order::userCenter_selected()
{
    qDebug() << "center ";
}

void order::quit_selected()
{
    this->close();
    emit quit();
}

void order::setpys(pay * p)
{
    pys = p;
}

void order::setmanage(Manage *m)
{
    manag = m;
}


