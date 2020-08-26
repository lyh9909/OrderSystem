#include "login_w.h"

void CheckUser::CreatConnect()
{
    ConnectSQLODBC cnt("QODBC", "localhost", "Test", "", "");   //建立连接
    if(cnt.OpenDataBase())      //如果可以连接数据库，进行查询
    {
        udb = new UseODBCDataBase(cnt.GetSqlDatabase());
    }
}

bool CheckUser::IsTheSame(const QString & username, const QString & password, const QString & power)
{
    QVector<QString> res = udb->ExecFindData("Accounts", "Username", username, 4);
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

bool CheckUser::IsVip(const QString &username,const QString & vip)
{
    QVector<QString> res = udb->ExecFindData("Accounts", "Username",username, 4);
    if(res.size())  //判断用户是否为会员
    {
        if(res[2] == vip)
            return true;
        else
            return false;
    }
    else
        return false;
}

void SignUpUser::CreatConnect()
{
    ConnectSQLODBC cnt("QODBC", "localhost", "Test", "", "");
    if(cnt.OpenDataBase())
    {
        udb = new UseODBCDataBase(cnt.GetSqlDatabase());
    }
}

bool SignUpUser::IsExist(const QString & username)
{
    QVector<QString> res = udb->ExecFindData("Accounts", "Username", username, 3);
    if(res.size() == 0)     //判断用户名是否存在
        return false;
    else
        return true;
}

bool SignUpUser::SignUp(const QString & username, const QString & password, const QString & power)
{
    if(IsExist(username))   //如果用户名存在 则提示警告
    {
        QMessageBox::warning(0, "Error", "The account is existed! Please change your username");
        return false;
    }
    //没有报错则进行注册
    QVector<QString> temp = {username, password, power};
    udb->ExecInsertData("Accounts", temp);
    if(IsExist(username))
        return true;
    else
        return false;
}

