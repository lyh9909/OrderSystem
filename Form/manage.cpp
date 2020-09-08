#include "manage.h"
#include "ui_manage.h"


Manage::Manage(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Manage), uodbc(nullptr)
{
    ui->setupUi(this);
    InitStatiusModel();
    InitOrderModel();
    InitModel();
    colnames.push_back("dishnumber");   //创建列名列表
    colnames.push_back("dishname");
    colnames.push_back("dishprice");
    colnames.push_back("dishsell");
    ordercolnames.push_back("ordernumber");
    ordercolnames.push_back("orderuser");
    ordercolnames.push_back("totalprice");
    ordercolnames.push_back("ordercontent");
}

Manage::~Manage()
{
    delete ui;
}

void Manage::InitModel()
{
     connectsql();  //连接数据库
     QVector<ItemData> datas;
     QVector<QString> typenames;
     getdishes(datas, typenames);      //获取菜品数据
     for(int i = 0; i < 6; ++i)
     {
         ItemModel.push_back(new QStandardItemModel());
     }
     for(int i = datas.size()-1; i >= 0; --i)   //逐一添加卡片
     {
         QStandardItem * Item = new QStandardItem;
         Item->setData(QVariant::fromValue(datas[i]), Qt::UserRole+1); //设置卡片数据
         ItemModel[gettypenum(typenames[i])]->appendRow(Item);    //按类别添加卡片
     }
     ItemDesigner = new ItemStyleDesigner(this);
     for(int i = 0; i < 6; ++i)
     {
         gettype(i)->setItemDelegate(ItemDesigner);
         gettype(i)->setSpacing(32);
         connect(gettype(i),SIGNAL(clicked(QModelIndex)),this,SLOT(itemClicked(QModelIndex)));    //设置信号槽
         myProxy.push_back(new QSortFilterProxyModel(gettype(i)));
         myProxy[i]->setSourceModel(ItemModel[i]);      //设置代理
         myProxy[i]->setFilterRole(Qt::UserRole);       //设置过滤器
         myProxy[i]->setDynamicSortFilter(true);        //设置动态排序过滤
         gettype(i)->setModel(myProxy[i]);      //设置模型
         gettype(i)->setViewMode(QListView::IconMode);      //设置窗口模式
         gettype(i)->setDragEnabled(false);     //关闭xx使能
     }
}

void Manage::on_Add_dish_clicked()
{
//    ItemData itm;   //保存修改后的数据
//    QDialog * dialog = new QDialog(this);       //创建新对话框
//    QFormLayout form(dialog);   //为对话框添加按钮和输入框
//    QLineEdit * input1 = new QLineEdit(dialog);     //添加输入框
//    form.addRow("NO     : ", input1);
//    QLineEdit * input2 = new QLineEdit(dialog);
//    form.addRow("Name   : ", input2);
//    QLineEdit * input3 = new QLineEdit(dialog);
//    form.addRow("Price  : ", input3);
//    QLineEdit * input4 = new QLineEdit(dialog);
//    form.addRow("Numbers: ", input4);
//    QDialogButtonBox butbox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel,Qt::Horizontal, dialog);    //添加按钮
//    form.addRow(&butbox);
//    connect(&butbox, SIGNAL(accepted()), dialog, SLOT(accept()) );      //连接信号和槽
//    connect(&butbox, SIGNAL(rejected()), dialog, SLOT(reject()) );
//    if(dialog->exec() == QDialog::Accepted) //如果点击OK 则
//    {
//        QVector<QString> temp;
//        temp.push_back(gettypename());      //存储要添加的数据
//        temp.push_back(input1->text());
//        temp.push_back(input2->text());
//        temp.push_back(input3->text());
//        temp.push_back(input4->text());
//        connectsql();       //连接数据库
//        uodbc->ExecInsertData("Dishs", temp);       //插入新数据
//        itm.number = input1->text();    //存储结构体，以便添加卡片
//        itm.name = input2->text();
//        itm.price = input3->text();
//        itm.num = input4->text();
//        QStandardItem * Item = new QStandardItem;       //添加item
//        Item->setData(QVariant::fromValue(itm), Qt::UserRole+1);
//        ItemModel[ui->DishsSelect->currentIndex()]->appendRow(Item);    //在对应Listview添加item
//    }

    dialog_pic * dlg = new dialog_pic();
    if(dlg->exec() == QDialog::Accepted)
    {
        DishItemData ditem = dlg->getdata();
        QStandardItem * Item = new QStandardItem;
        Item->setData(QVariant::fromValue(ditem), Qt::UserRole+1); //设置卡片数据
        Item->setData(ditem.Dishtype, Qt::UserRole+2);
        ItemModel[ui->DishsSelect->currentIndex()]->appendRow(Item);    //按类别添加卡片
    }

}

void Manage::itemClicked(QModelIndex index)
{

}

void Manage::connectsql()
{
    ConnectSQLODBC db("QODBC", "172.20.10.2", "Test", "root", "only123456");    //连接数据库
    if(db.OpenDataBase())
    {
        uodbc = new UseODBCDataBase(db.GetSqlDatabase());
    }
}

void Manage::getdishes(QVector<ItemData> & ida, QVector<QString> & types)
{
    QVector<QVector<QString> > res =  uodbc->ExecGetAllData("Dishs", 5);       //获取所有数据
    if(res.size() == 0)
        return;
    int rows = res.size();
    for(int i = 0; i < rows; ++i)       //将获取到的数据存入结构体和字符串中，以便添加卡片
    {
        ItemData itemdata;
        itemdata.name = res[i][2];
        itemdata.price = res[i][3];
        itemdata.number = res[i][1];
        itemdata.num = res[i][4];
        types.push_back(res[i][0]);
        ida.push_back(itemdata);
    }
}

void Manage::on_DishsSelect_currentChanged(int index)
{

}

void Manage::on_Change_dish_clicked()
{
    QListView * qls = gettype();    //获取选中的类型
    QVariant qv = (qls->currentIndex()).data(Qt::UserRole+1);
    ItemData itm = qv.value<ItemData>();    //获取选中的卡片数据
    QDialog * dialog = new QDialog(this);   //创建对话框
    QFormLayout form(dialog);
    QLineEdit * input1 = new QLineEdit(dialog);     //创建输入框和按钮
    input1->setText(itm.number);
    form.addRow("NO     : ", input1);
    QLineEdit * input2 = new QLineEdit(dialog);
    input2->setText(itm.name);
    form.addRow("Name   : ", input2);
    QLineEdit * input3 = new QLineEdit(dialog);
    input3->setText(itm.price);
    form.addRow("Price  : ", input3);
    QLineEdit * input4 = new QLineEdit(dialog);
    input4->setText(itm.num);
    form.addRow("Numbers: ", input4);
    QDialogButtonBox butbox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel,Qt::Horizontal, dialog);
    form.addRow(&butbox);
    connect(&butbox, SIGNAL(accepted()), dialog, SLOT(accept()) );
    connect(&butbox, SIGNAL(rejected()), dialog, SLOT(reject()) );
    if(dialog->exec() == QDialog::Accepted)     //如果点击OK 则
    {
        QVector<QString> temp;  //存储修改后的数据
        temp.push_back(input1->text());
        temp.push_back(input2->text());
        temp.push_back(input3->text());
        temp.push_back(input4->text());
        connectsql();       //连接数据库
        uodbc->ExecUpdataData("Dishs", "dishname", itm.name, colnames, temp);       //更新数据库数据
        itm.number = input1->text();
        itm.name = input2->text();
        itm.price = input3->text();
        itm.num = input4->text();   //刷新卡片
        QModelIndexList lists;      //获取索引列表
        lists<<myProxy[ui->DishsSelect->currentIndex()]->mapToSource(qls->currentIndex());     //获取绝对索引
        ItemModel[ui->DishsSelect->currentIndex()]->setData(lists[0], QVariant::fromValue(itm), Qt::UserRole+1);     //修改选中的卡片
    }
}


void Manage::on_Delete_dish_clicked()
{
    QListView * qls = gettype();
    QVariant qv = (qls->currentIndex()).data(Qt::UserRole+1);
    ItemData itm = qv.value<ItemData>();
    connectsql();
    uodbc->ExecDeleteData("Dishs", "dishname", itm.name);   //移除数据库对应的数据
    ItemModel[ui->DishsSelect->currentIndex()]->removeRow(qls->currentIndex().row());      //移除选中的卡片
}

QListView * Manage::gettype(int n)      //根据编号获取对应对象
{
    int index = n == -1 ? ui->DishsSelect->currentIndex() : n;
    switch(index)
    {
        case 0: return ui->Show_Rice; break;
        case 1: return ui->Show_Noodle; break;
        case 2: return ui->Show_Soup; break;
        case 3: return ui->Show_Snack; break;
        case 4: return ui->Show_Drink; break;
        case 5: return ui->Show_Fire; break;
    }
}

QString Manage::gettypename()   //获取当前选项栏对应的菜品类别名称
{
    int index = ui->DishsSelect->currentIndex();
    switch(index)
    {
        case 0: return QString("rice"); break;
        case 1: return QString("noodle"); break;
        case 2: return QString("soup"); break;
        case 3: return QString("snack"); break;
        case 4: return QString("drink"); break;
        case 5: return QString("fire"); break;
    }
}

int Manage::gettypenum(QString & q) //获取字符串对应的序号
{
    if(q == "饭")
        return 0;
    else if(q == "面食")
        return 1;
    else if(q == "汤")
        return 2;
    else if(q == "小吃")
        return 3;
    else if(q == "饮品")
        return 4;
    else
        return 5;
}

void Manage::InitOrderModel()
{
    OrderItemModel = new QStandardItemModel();
    QVector<ItemOrderData> idata;
    connectsql();
    getorders(idata);
    for(int i = 0; i < idata.size(); ++i)
    {
        QStandardItem * Item = new QStandardItem;
        Item->setData(QVariant::fromValue(idata[i]), Qt::UserRole+1);
        OrderItemModel->appendRow(Item);
    }
    OrderItemDesigner = new ItemOrderDesigner(this);
    ui->Order_Show->setItemDelegate(OrderItemDesigner);
    ui->Order_Show->setSpacing(30);
    connect(ui->Order_Show,SIGNAL(clicked(QModelIndex)),this,SLOT(itemClicked(QModelIndex)));    //设置信号槽
    OrdermyProxy = new QSortFilterProxyModel(ui->Order_Show);
    OrdermyProxy->setSourceModel(OrderItemModel);      //设置代理
    OrdermyProxy->setFilterRole(Qt::UserRole);       //设置过滤器
    OrdermyProxy->setDynamicSortFilter(true);        //设置动态排序过滤
    ui->Order_Show->setModel(OrdermyProxy);      //设置模型
    ui->Order_Show->setViewMode(QListView::IconMode);      //设置窗口模式
    ui->Order_Show->setDragEnabled(false);     //关闭xx使能
}

void Manage::getorders(QVector<ItemOrderData> & ida)
{
    QVector<QVector<QString> > res =  uodbc->ExecGetAllData("Orders", 4);       //获取所有数据
    if(res.size() == 0)
        return;
    int rows = res.size();
    for(int i = 0; i < rows; ++i)       //将获取到的数据存入结构体和字符串中，以便添加卡片
    {
        ItemOrderData itemdata;
        itemdata.onumber = res[i][0];
        itemdata.ouser = res[i][1];
        itemdata.totalprice = res[i][2];
        itemdata.content = res[i][3];
        ida.push_back(itemdata);
    }
}

void Manage::on_Change_Order_clicked()
{
    QVariant qv = (ui->Order_Show->currentIndex()).data(Qt::UserRole+1);
    ItemOrderData itm = qv.value<ItemOrderData>();    //获取选中的卡片数据
    QDialog * dialog = new QDialog(this);   //创建对话框
    QFormLayout form(dialog);
    QLineEdit * input1 = new QLineEdit(dialog);     //创建输入框和按钮
    input1->setText(itm.onumber);
    form.addRow("NO             : ", input1);
    QLineEdit * input2 = new QLineEdit(dialog);
    input2->setText(itm.ouser);
    form.addRow("Order Person   : ", input2);
    QLineEdit * input3 = new QLineEdit(dialog);
    input3->setText(itm.totalprice);
    form.addRow("Total Price    : ", input3);
    QLineEdit * input4 = new QLineEdit(dialog);
    input4->setText(itm.content);
    form.addRow("Order Content  : ", input4);
    QDialogButtonBox butbox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel,Qt::Horizontal, dialog);
    form.addRow(&butbox);
    connect(&butbox, SIGNAL(accepted()), dialog, SLOT(accept()) );
    connect(&butbox, SIGNAL(rejected()), dialog, SLOT(reject()) );
    if(dialog->exec() == QDialog::Accepted)     //如果点击OK 则
    {
        QVector<QString> temp;  //存储修改后的数据
        temp.push_back(input1->text());
        temp.push_back(input2->text());
        temp.push_back(input3->text());
        temp.push_back(input4->text());
        connectsql();       //连接数据库
        uodbc->ExecUpdataData("Orders", "ordernumber", itm.onumber, ordercolnames, temp);       //更新数据库数据
        itm.onumber = input1->text();
        itm.ouser = input2->text();
        itm.totalprice = input3->text();
        itm.content = input4->text();   //刷新卡片
        QModelIndexList lists;      //获取索引列表
        lists << OrdermyProxy->mapToSource(ui->Order_Show->currentIndex());     //获取绝对索引
        OrderItemModel->setData(lists[0], QVariant::fromValue(itm), Qt::UserRole+1);     //修改选中的卡片
    }
}

void Manage::on_Delete_Order_clicked()
{
    QListView * qls = ui->Order_Show;
    QVariant qv = (qls->currentIndex()).data(Qt::UserRole+1);
    ItemOrderData itm = qv.value<ItemOrderData>();
    connectsql();
    uodbc->ExecDeleteData("Orders", "ordernumber", itm.onumber);   //移除数据库对应的数据
    OrderItemModel->removeRow(qls->currentIndex().row());      //移除选中的卡片
}

void Manage::InitStatiusModel()
{
    connectsql();  //连接数据库
    QVector<ItemStatiusData> d_datas;
    QVector<ItemStatiusData> p_datas;
    QMap<QString, int> tmap;
    float t_price = 0;
    getstatius(d_datas, 0);      //获取数据
    getstatius(p_datas, 1);      //获取数据
    int index = 0;
    int max = 0;
    for(int i = 0; i < 2; ++i)
    {
        StatiusItemModel.push_back(new QStandardItemModel());
    }
    for(int i = d_datas.size()-1; i >= 0; --i)   //逐一添加卡片
    {
        if(d_datas[i].counts.toInt() > max)
        {
            max = d_datas[i].counts.toInt();
            index = i;
        }
        QStandardItem * Item = new QStandardItem;
        Item->setData(QVariant::fromValue(d_datas[i]), Qt::UserRole+1); //设置卡片数据
        StatiusItemModel[0]->appendRow(Item);    //按类别添加卡片
    }
    for(int i = p_datas.size()-1; i >= 0; --i)  //利用map统计点餐次数
    {
        if(tmap.find(p_datas[i].name) == tmap.end())
        {
            tmap.insert(p_datas[i].name, 1);
        }
        else
            tmap[p_datas[i].name] += 1;
        t_price += p_datas[i].counts.toFloat();
    }
    QList<QString> qttemp = tmap.keys();
    for(int i = 0; i < qttemp.size(); ++i)
    {
        ItemStatiusData temp = {qttemp.value(i) , QString::number(tmap[qttemp.value(i)])};
        QStandardItem * Item = new QStandardItem;
        Item->setData(QVariant::fromValue(temp), Qt::UserRole+1); //设置卡片数据
        StatiusItemModel[1]->appendRow(Item);    //按类别添加卡片
    }
    StatiusDesigner = new ItemStatiusDesigner(this);
    for(int i = 0; i < 2; ++i)
    {
        getstatiustype(i)->setItemDelegate(StatiusDesigner);
        getstatiustype(i)->setSpacing(32);
        connect(getstatiustype(i),SIGNAL(clicked(QModelIndex)),this,SLOT(itemClicked(QModelIndex)));    //设置信号槽
        StatiusmyProxy.push_back(new QSortFilterProxyModel(getstatiustype(i)));
        StatiusmyProxy[i]->setSourceModel(StatiusItemModel[i]);      //设置代理
        StatiusmyProxy[i]->setFilterRole(Qt::UserRole);       //设置过滤器
        StatiusmyProxy[i]->setDynamicSortFilter(true);        //设置动态排序过滤
        getstatiustype(i)->setModel(StatiusmyProxy[i]);      //设置模型
        getstatiustype(i)->setViewMode(QListView::IconMode);      //设置窗口模式
        getstatiustype(i)->setDragEnabled(false);     //关闭xx使能
    }
    ui->total_income->setText(QString::number(t_price));
    ui->most_popular->setText(d_datas[index].name);
}

void Manage::getstatius(QVector<ItemStatiusData> & ida, int n)
{
    QVector<QString> coln;
    QVector<QVector<QString> > res;
    if(n == 0)
    {
        coln.push_back("dishname");     //获取菜品名和销量数据
        coln.push_back("dishsell");
        res =  uodbc->ExecGetSomeData("Dishs", coln) ;
    }
    else
    {
        coln.push_back("orderuser");
        coln.push_back("totalprice");
        res =  uodbc->ExecGetSomeData("Orders", coln) ;
    }
    if(res.size() == 0)
        return;
    int rows = res.size();
    for(int i = 0; i < rows; ++i)       //将获取到的数据存入结构体和字符串中，以便添加卡片
    {
        ItemStatiusData itemdata;
        itemdata.name = res[i][0];
        itemdata.counts = res[i][1];
        ida.push_back(itemdata);
    }
}

QListView * Manage::getstatiustype(int n)
{
    switch(n)
    {
        case 0: return ui->statius_dish; break;
        case 1: return ui->statius_order;break;
    }
}

void Manage::manageShow()
{
    this->show();
}

