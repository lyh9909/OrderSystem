#ifndef SQL_CONNECT_H
#define SQL_CONNECT_H

#include <QtSql>
#include <QDialog>
#include <QDebug>
#include <QMessageBox>
#include <QSqlError>
#include <QSqlDatabase>
#include <QSqlQuery>

//抽象类，用于创建连接
class BaseConnectDataBase
{
public:
    virtual ~BaseConnectDataBase(){}
    virtual bool OpenDataBase() = 0;    //创建数据库连接
    virtual void CloseDataBase() = 0;   //关闭数据库
    virtual bool ReOpenDataBase() = 0;  //重新开启连接
    virtual void ClearConnect() = 0;    //清除连接
    virtual void SetDataSource(const QString & sourcename) = 0; //设置数据库源名称
    virtual void SetHostAddress(const QString & ip) = 0;     //设置数据库主机地址或名称
    virtual void SetUserandPwd(const QString & user, const QString & pwd) = 0;      //设置数据库登陆用户名和登陆密码
    virtual void SetDataType(const QString & type) = 0;     //设置数据库类型
    virtual QSqlDatabase & GetSqlDatabase() = 0;        //获得已创建的数据库连接对象，用于查询等其它操作
};

//实现类，用于连接Sql ODBC数据源
class ConnectSQLODBC : public BaseConnectDataBase
{
private:
    QString datatype;   //数据库类型
    QString hostname;   //数据库主机地址或名称
    QString datasourcename;    //数据库源名称
    QString username;   //数据库登陆用户名
    QString password;   //数据库登陆密码
    QSqlDatabase db;    //数据库连接对象
public:
    ConnectSQLODBC(){}
    ConnectSQLODBC(const QString & dtype, const QString & hname, const QString & dsname, const QString & uname, const QString & pwd):
        datatype(dtype), hostname(hname), datasourcename(dsname), username(uname), password(pwd) {}
    virtual bool OpenDataBase();
    virtual void CloseDataBase();
    virtual bool ReOpenDataBase();
    virtual void ClearConnect();
    virtual void SetDataSource(const QString & sourcename);
    virtual void SetHostAddress(const QString & ip);
    virtual void SetUserandPwd(const QString & user, const QString & pwd);
    virtual void SetDataType(const QString & type);
    virtual QSqlDatabase & GetSqlDatabase();
};

//抽象类， 用于对数据库进行操作
class UseDataBase
{
public:
    virtual ~UseDataBase(){}
    virtual QVector<QVector<QString> > ExecGetAllData(const QString & tablename, int nums) = 0;    //获取所有数据
    virtual QVector<QString> ExecGetOneData(const QString & tablename, const QString & colname) = 0;  //获取某列数据
    virtual QVector<QVector<QString> > ExecGetSomeData(const QString & tablename, const QVector<QString> & colname) = 0;  //获取某些列数据
    virtual void ExecInsertData(const QString & tablename, const QVector<QString> & datas) = 0;     //插入数据
    virtual void ExecUpdataData(const QString & tablename, const QString & colname, const QString & coldata,
                                const QVector<QString> & colnames, const QVector<QString> & datas) = 0;   //修改数据
    virtual void ExecChangeData(const QString & tablename, const QString & colname, const QString & datas,
                                         const QString & newcol,const QString & newdata) = 0;
    virtual void ExecDeleteData(const QString & tablename, const QString & colname, const QString & datas) = 0;   //删除数据
    virtual QVector<QString> ExecFindData(const QString & tablename, const QString & colname, const QString & datas, int nums) = 0;     //查找指定数据
    virtual QVector<QVector<QString> > ExecGetSpecData(const QString & tablename, const QString & colname, const QString & datas, int nums) = 0; //获取指定数据
};

//实现类 用于对ODBC SQL数据库进行操作
class UseODBCDataBase : public UseDataBase
{
private:
    QSqlQuery sql;
public:
    UseODBCDataBase(QSqlDatabase & db)
    {
        sql = QSqlQuery(db);
    }
    virtual QVector<QVector<QString> > ExecGetAllData(const QString & tablename, int nums);
    virtual QVector<QVector<QString> > ExecGetSomeData(const QString & tablename, const QVector<QString> & colname);
    virtual QVector<QString> ExecGetOneData(const QString & tablename, const QString & colname);
    virtual void ExecInsertData(const QString & tablename, const QVector<QString> & datas);
    virtual void ExecUpdataData(const QString & tablename, const QString & colname, const QString & coldata,
                                const QVector<QString> & colnames, const QVector<QString> & datas);
    virtual void ExecChangeData(const QString & tablename, const QString & colname, const QString & datas,
                                         const QString & newcol,const QString & newdata);
    virtual void ExecDeleteData(const QString & tablename, const QString & colname, const QString & datas);
    virtual QVector<QString> ExecFindData(const QString & tablename, const QString & colname, const QString & datas, int nums);     //查找指定数据
    virtual QVector<QVector<QString> > ExecGetSpecData(const QString & tablename, const QString & colname, const QString & datas, int nums); //获取指定数据
};


#endif // SQL_CONNECT_H
