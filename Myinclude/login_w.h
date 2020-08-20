#ifndef LOGINW_H
#define LOGINW_H

#include "sql_connect.h"

//抽象类 检查是否满足登陆要求
class BaseCheckUser
{
public:
    virtual ~BaseCheckUser() {}
    virtual void CreatConnect() = 0;    //创建连接
    virtual bool IsTheSame(const QString & username, const QString & password, const QString & power) = 0;      //判断是否相同
};

class CheckUser : public BaseCheckUser
{
private:
    UseODBCDataBase * udb;
public:
    CheckUser() : udb(nullptr){}
    virtual void CreatConnect();
    virtual bool IsTheSame(const QString & username, const QString & password, const QString & power);
};

//抽象类 判断是否满足注册条件并注册
class BaseSignUpUser
{
public:
    virtual ~BaseSignUpUser(){}
    virtual void CreatConnect() = 0;    //创建连接
    virtual bool IsExist(const QString & username) = 0;     //判断账户是否存在
    virtual bool SignUp(const QString & username, const QString & password, const QString & power) = 0;     //进行注册 并返回是否注册成功
};

class SignUpUser : public BaseSignUpUser
{
private:
    UseODBCDataBase * udb;
public:
    SignUpUser() : udb(nullptr){}
    virtual void CreatConnect();
    virtual bool IsExist(const QString & username);
    virtual bool SignUp(const QString & username, const QString & password, const QString & power);
};

#endif // LOGIN_H
