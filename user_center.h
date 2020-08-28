#ifndef USER_CENTER_H
#define USER_CENTER_H

#include <QWidget>
#include "Myinclude/DrawItem.h"
#include "Myinclude/sql_connect.h"
#include <QStandardItem>
#include <QStandardItemModel>
#include <QModelIndex>

namespace Ui {
class user_center;
}

class user_center : public QWidget
{
    Q_OBJECT

public:
    explicit user_center(QWidget *parent = nullptr);
    ~user_center();

    void setAll(QModelIndexList modelIndexList);

signals:
    void ret();
    void payShow();

private:
    Ui::user_center *ui;
    QStandardItemModel *m_model;
    ItemDelegate *m_delegate;

private slots:
    void ucShow();
    void on_returnBtn_clicked();
    void on_payBtn_clicked();

};

#endif // USER_CENTER_H
