#ifndef LOGIN_MANAGE_H
#define LOGIN_MANAGE_H

#include <QWidget>
#include "Myinclude/login_w.h"


namespace Ui {
class login_manage;
}

class login_manage : public QWidget
{
    Q_OBJECT

public:
    explicit login_manage(QWidget *parent = nullptr);
    ~login_manage();


private slots:
    void on_Button_SignIn_clicked();

    void loginManageShow();

signals:
    void manageShow();

private:
    Ui::login_manage *ui;
};

#endif // LOGIN_MANAGE_H
