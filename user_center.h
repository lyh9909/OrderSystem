#ifndef USER_CENTER_H
#define USER_CENTER_H

#include <QWidget>
#include "Myinclude/sql_connect.h"

namespace Ui {
class user_center;
}

class user_center : public QWidget
{
    Q_OBJECT

public:
    explicit user_center(QWidget *parent = nullptr);
    ~user_center();

signals:
    void quit();

private:
    Ui::user_center *ui;

private slots:
    void ucShow();
    void on_quitBtn_clicked();
};

#endif // USER_CENTER_H
