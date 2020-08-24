#include "login.h"
#include "ui_login.h"


login::login(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::login)
{
    ui->setupUi(this);
}

login::~login()
{
    delete ui;
}


void login::on_Button_SignIn_clicked()
{
    CheckUser * chs = new CheckUser();
    chs->CreatConnect();        //创建连接
    if(chs->IsTheSame(ui->Input_User->text(), ui->Input_Password->text(), "0"))     //检查用户名密码权限是否正确
    {
        emit orderShow();
        oo->userName(ui->Input_User->text());
        this->hide();
    }
    else
        QMessageBox::warning(0, "Sorry", "Username or Password is Wrong, or Power isn't Match");
    delete chs;
}

void login::on_Button_SignUp_clicked()
{
    SignUpUser * suu = new SignUpUser();    //同上
    suu->CreatConnect();
    if(suu->SignUp(ui->Input_User->text(), ui->Input_Password->text(), "0"))
    {
        QMessageBox::warning(0, "Tips", "Sign Up Success");
    }
    else
    {
        QMessageBox::warning(0, "Error", "Sign Up Error");
    }
}

void login::loginShow()
{
    this->show();
    ui->Input_Password->setText(QString(""));
}

void login::setOrder(order *o)
{
    oo = o;
}
