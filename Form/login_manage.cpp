#include "login_manage.h"
#include "ui_login_manage.h"

login_manage::login_manage(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::login_manage)
{
    ui->setupUi(this);
}

login_manage::~login_manage()
{
    delete ui;
}

void login_manage::on_Button_SignIn_clicked()
{
    CheckUser * chs = new CheckUser();
    chs->CreatConnect();    //创建连接
    if(chs->IsTheSame(ui->Input_User->text(), ui->Input_Password->text(), "1"))     //检查用户名密码权限是否正确
    {
        emit manageShow();
        this->hide();

    }
    else
        QMessageBox::warning(0, "Sorry", "Username or Password is Wrong, or Power isn't Match");
    delete chs;
}

void login_manage::loginManageShow()
{
    this->show();
}



