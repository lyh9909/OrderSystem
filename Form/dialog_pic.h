#ifndef DIALOG_PIC_H
#define DIALOG_PIC_H

#include <QPixmap>
#include <QDialog>
#include <QFileDialog>
#include <QDir>
#include "Form/structs.h"
#include "Myinclude/sql_connect.h"

#ifdef _MSC_VER
#pragma execution_character_set("utf-8")
#endif

namespace Ui {
class dialog_pic;
}

class dialog_pic : public QDialog
{
    Q_OBJECT

public:
    explicit dialog_pic(QWidget *parent = nullptr);
    ~dialog_pic();
    DishItemData getdata();


private slots:
    void on_buttonBox_accepted();

    void on_buttonBox_rejected();

    void on_addpicture_clicked();

private:
    Ui::dialog_pic *ui;
    QString dishtype;
    QString dishname;
    QString dishprice;
    QPixmap dishphoto;
    QByteArray b_dishphoto;
};

#endif // DIALOG_PIC_H
