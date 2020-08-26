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
    ui->payPrice->setText(QString::number(price));
}


void pay::on_payBtn_clicked()
{

//    ConnectSQLODBC db("QODBC", "localhost", "Test", "", "");    //连接数据库
//    if(db.OpenDataBase())
//    {
//        uodbc = new UseODBCDataBase(db.GetSqlDatabase());
//    }
//    QVector<QString> temp;
//    uodbc->ExecInsertData("orders", temp);       //插入新数据

//    QByteArray data;
//    QString filename = QFileDialog::getOpenFileName(
//                    this,
//                    "Open Document",
//                    QDir::currentPath(),
//                    "Document files (*.jpg *.png);;All files(*.*)"
//                );
    QDialog * dlg = new QDialog(this);  //创建对话框
    QFormLayout form(dlg);      //创建窗体
    QLabel * lab = new QLabel(dlg);     //创建label 用于存放图片
    QImage * img = new QImage;      //用于读取图片
//    if (!filename.isEmpty())
//    {
//        QPixmap *pixmap=new QPixmap(filename);
//        lab->setPixmap(pixmap->scaled(ui->label->width(),ui->label->height()));
//        QFile *file=new QFile(filename); //fileName为二进制数据文件名
//        file->open(QIODevice::ReadOnly);
//        data = file->readAll();
//        file->close();
//    }


//    if(db.OpenDataBase())
//    {
//        QSqlQuery query;
//        query.exec("SELECT * FROM photo");
//        QPixmap photo;
//        query.first();
//        photo.loadFromData(query.value(1).toByteArray(), "jpg");
//        lab->setPixmap(photo);
//    }

    img->load(":/new/Pic_/Picture/Test.png");   //加载图片
    lab->setPixmap(QPixmap::fromImage(*img));   //设置图片
    lab->show();    //显示图片
//    form.addRow(lab);
//    if(dlg->exec() == QDialog::Accepted)    //弹出对话框
//    {

//    }
}

void pay::on_cancelBtn_clicked()
{
    emit ucShow();
    this->close();
}

void pay::payShow()
{
    this->show();
}

