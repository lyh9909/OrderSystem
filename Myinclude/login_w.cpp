﻿#include "login_w.h"

void CheckUser::CreatConnect()
{
    ConnectSQLODBC cnt("QODBC", "172.20.10.2", "Test","root", "only123456");   //建立连接
    if(cnt.OpenDataBase())      //如果可以连接数据库，进行查询
    {
        udb = new UseODBCDataBase(cnt.GetSqlDatabase());
    }
}

bool CheckUser::IsTheSame(const QString & username, const QString & password, const QString & power)
{
    QVector<QString> res = udb->ExecFindData("Accounts", "Username", username, 4);
    qDebug()<<res.size();
    if(res.size())  //如果用户存在， 判断密码和权限是否正确
    {
        if(res[0] == password && res[1] == power)
            return true;
        else
            return false;
    }
    else
        return false;
}

int CheckUser::Vip(const QString &username)
{
    QVector<QString> res = udb->ExecFindData("Accounts", "Username",username, 4);
    if(res.size())
    {
        if(res[2] == "1")
            return 1;
        else if(res[2] == "2")
            return 2;
        else if(res[2] == "3")
            return 3;
        else
            return 0;
    }
    else
        return 0;
}

void SignUpUser::CreatConnect()
{
    cnt = new ConnectSQLODBC("QODBC", "172.20.10.2", "Test", "root", "only123456");
}

bool SignUpUser::IsExist(const QString & username)
{
    if(cnt->OpenDataBase())
    {
        udb = new UseODBCDataBase(cnt->GetSqlDatabase());
    }
    QVector<QString> res = udb->ExecFindData("Accounts", "Username", username, 3);
    if(res.size() == 0)     //判断用户名是否存在
        return false;
    else
        return true;
}

bool SignUpUser::SignUp(const QString & username, const QString & password, const QString & power)
{
    if(cnt->OpenDataBase())
    {
        udb = new UseODBCDataBase(cnt->GetSqlDatabase());
    }
    if(IsExist(username))   //如果用户名存在 则提示警告
    {
        QMessageBox::warning(0, "Error", "The account is existed! Please change your username");
        return false;
    }
    //没有报错则进行注册
    QVector<QString> temp = {username, password, power, "0"};
    udb->ExecInsertData("Accounts", temp);
    if(IsExist(username))
        return true;
    else
        return false;
}

