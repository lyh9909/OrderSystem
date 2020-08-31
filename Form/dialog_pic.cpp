#include "dialog_pic.h"
#include "ui_dialog_pic.h"

dialog_pic::dialog_pic(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::dialog_pic)
{
    ui->setupUi(this);
}

dialog_pic::~dialog_pic()
{
    delete ui;
}

void dialog_pic::on_buttonBox_accepted()
{
    dishtype = ui->selecttype->currentText();
    dishname = ui->inputname->text();
    dishprice = ui->inputprice->text();
    ConnectSQLODBC db("QODBC", "localhost", "Test", "", "");
    QSqlQuery sql = QSqlQuery(db.GetSqlDatabase());
    sql.prepare("INSERT INTO Dishs (dishtype, dishname, dishphoto, dishprice)"
                " VALUES(:dishtype, :dishname, :dishphoto, :dishprice)");
    sql.bindValue(":dishtype", dishtype);
    sql.bindValue(":dishname",dishname);
    sql.bindValue(":dishphoto",b_dishphoto);
    sql.bindValue(":dishprice",dishprice.toDouble());
    sql.exec();
    this->close();
}

void dialog_pic::on_buttonBox_rejected()
{

}

void dialog_pic::on_addpicture_clicked()
{
    QString filename = QFileDialog::getOpenFileName(
                    this,
                    "Open Document",
                    QDir::currentPath(),
                    "Document files (*.png);;All files(*.*)"
                );
    if(!filename.isEmpty())
    {
        dishphoto.load(filename);
        ui->label->setPixmap(dishphoto);
        QFile * file = new QFile(filename); //fileName为二进制数据文件名
        file->open(QIODevice::ReadOnly);
        b_dishphoto = file->readAll();
        file->close();
    }
}

DishItemData dialog_pic::getdata()
{
    DishItemData temp = {dishtype, dishname, dishphoto, dishprice.toDouble()};
    return temp;
}





