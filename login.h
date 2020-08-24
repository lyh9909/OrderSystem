#ifndef LOGIN_H
#define LOGIN_H

#include <QWidget>
#include "Myinclude/login_w.h"
#include "Myinclude/order.h"

QT_BEGIN_NAMESPACE
namespace Ui { class login; }
QT_END_NAMESPACE

class login : public QWidget
{
    Q_OBJECT

public:
    login(QWidget *parent = nullptr);
    ~login();
    void setOrder(order *o);

private slots:
    void on_Button_SignIn_clicked();

    void on_Button_SignUp_clicked();

    void loginShow();

signals:
    void orderShow();


private:
    Ui::login *ui;
    order *oo;

};
#endif // LOGIN_H
