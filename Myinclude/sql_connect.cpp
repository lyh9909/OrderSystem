#include "sql_connect.h"

void ConnectSQLODBC::SetDataSource(const QString & sourcename)
{
    datasourcename = sourcename;
}

void ConnectSQLODBC::SetHostAddress(const QString & ip)
{
    hostname = ip;
}

void ConnectSQLODBC::SetUserandPwd(const QString & user, const QString & pwd)
{
    username = user;
    password = pwd;
}

void ConnectSQLODBC::SetDataType(const QString & type)
{
    datatype = type;
}

bool ConnectSQLODBC::OpenDataBase()
{
    db = QSqlDatabase::addDatabase(datatype);   //创建数据库对象
    if(!db.isValid())       //判断该数据库类型是否合法
    {
        qDebug() << "ODBC Driver Error" << endl;
        return false;
    }
    db.setHostName(hostname);       //设置主机地址
    db.setDatabaseName(datasourcename);     //设置数据库源
    db.setUserName(username);       //设置用户名
    db.setPassword(password);       //设置密码
    if(db.open())   //判断是否能打开数据库
    {
        qDebug() << "Connect DateBase Success!" << endl;
        return true;
    }
    else
    {
        qDebug() << "Open Faild";
        qDebug() << db.lastError().text();      //不能打开，输出错误原因
        return false;
    }
}

void ConnectSQLODBC::CloseDataBase()
{
    db.close();
}

void ConnectSQLODBC::ClearConnect()
{
    db.close();
    QString temp = db.databaseName();
    QSqlDatabase::removeDatabase(temp);
}

bool ConnectSQLODBC::ReOpenDataBase()
{
    if(db.open())
    {
        qDebug() << "Open Success";
        return true;
    }
    else
    {
        qDebug() << "Open Faild";
        qDebug() << db.lastError().text();
        return false;
    }
}

QSqlDatabase & ConnectSQLODBC::GetSqlDatabase()
{
    return db;      //返回已建立连接的数据库对象
}

QVector<QVector<QString> > UseODBCDataBase::ExecGetAllData(const QString & tablename, int nums)
{
    QVector<QVector<QString> > ans;  //创建返回数据列表
    if(tablename.size() == 0)       //如果表单名字为空， 返回空数组
        return ans;
    sql.exec("SELECT * FROM "+tablename);   //执行SQL语句， 查找所有数据
    while(sql.next())       //遍历各个数据，并将其加入数据列表
    {
        QVector<QString> temp;
        for(int i = 0; i < nums; ++i)
        {
            temp.push_back(sql.value(i).toString().simplified());
        }
        ans.push_back(temp);
    }
    return ans;
}

QVector<QString> UseODBCDataBase::ExecGetOneData(const QString & tablename, const QString & colname)
{
    QVector<QString> ans;   //创建返回数据列表
    if(tablename.size() == 0 || colname.size() == 0)    //如果表单名字为空或者列名为空， 返回空数组
        return ans;
    sql.exec("SELECT " + colname + " FROM " + tablename);   //执行SQL语句， 查找该列数据
    while(sql.next())   //遍历各个数据，并将其加入数据列表
    {
        ans.push_back(sql.value(0).toString().simplified());
    }
    return ans;
}

QVector<QVector<QString> > UseODBCDataBase::ExecGetSomeData(const QString & tablename, const QVector<QString> & colname)
{
    QVector<QVector<QString> > ans;     //创建返回数据列表
    if(tablename.size() == 0)   //如果表单名字为空， 返回空数组
        return ans;
    int length = colname.size();
    QString temp;
    for(int i = 0; i < length-1; ++i)   //按照SQL格式合并列名
    {
        temp += colname[i]+',';
    }
    temp += colname[length-1];
    sql.exec("SELECT " + temp + " FROM " + tablename);  //执行SQL语句，获取这些列的数据
    while(sql.next())   //遍历各个数据，并将其加入数据列表
    {
        QVector<QString> temps;
        for(int i = 0; i < length; ++i)
        {
            temps.push_back(sql.value(i).toString().simplified());
        }
        ans.push_back(temps);
    }
    return ans;
}

void UseODBCDataBase::ExecInsertData(const QString & tablename, const QVector<QString> & datas)
{
    if(tablename.size() == 0)
        return;
    int length = datas.size();
    QString temp;
    for(int i = 0; i < length-1; ++i)   //按照SQL格式合并列数据
    {
        temp += "\'" + datas[i] + "\', ";
    }
    temp += "\'" + datas[length-1]+"\'";
    sql.exec("INSERT INTO " + tablename + " VALUES (" + temp +")");     //执行SQL操作，插入数据
}

void UseODBCDataBase::ExecUpdataData(const QString & tablename, const QString & colname, const QString & coldata,
                                     const QVector<QString> & colnames,  const QVector<QString> & datas)
{
    if(tablename.size() == 0)
        return;
    int length = datas.size();
    QString temp;
    for(int i = 0; i < length-1; ++i)
    {
        temp += colnames[i] + " = " + "\'" + datas[i] + "\', ";
    }
    temp += colnames[length-1] + " = " + "\'" + datas[length-1] + "\' ";
    sql.exec("UPDATE " + tablename + " SET " + temp + " WHERE " + colname + " = \'" + coldata +"\'");   //执行SQL操作，更新数据
}

void UseODBCDataBase::ExecDeleteData(const QString & tablename, const QString & colname, const QString & datas)
{
    if(tablename.size() == 0)
        return;
    sql.exec("DELETE FROM " + tablename + " WHERE " + colname + " = " + "\'" + datas + "\'");   //执行SQL操作，删除数据
}

QVector<QString> UseODBCDataBase::ExecFindData(const QString &tablename, const QString &colname, const QString &datas, int nums)    //查找指定数据
{
    QVector<QString> ans;
    if(tablename.size() == 0)
        return ans;
    QString temp = colname + " = \'" + datas + "\'";
    sql.exec("SELECT * FROM " + tablename + " WHERE " + temp);      //执行SQL操作，查找指定数据
    if(sql.first())
    {
        for(int i = 1; i < nums; ++i)
        {
            ans.push_back(sql.value(i).toString().simplified());
        }
    }
    return ans;
}

QVector<QVector<QString> > UseODBCDataBase::ExecGetSpecData(const QString & tablename, const QString & colname, const QString & datas, int nums)
{
    QVector<QVector<QString> > ans;
    if(tablename.size() == 0)
        return ans;
    QString temp = colname + " = \'" + datas + "\'";
    sql.exec("SELECT * FROM " + tablename + " WHERE " + temp);      //执行SQL操作，查找指定数据
    while(sql.next())
    {
        QVector<QString> t;
        for(int i = 0; i < nums; ++i)
        {
            t.push_back(sql.value(i).toString().simplified());
        }
        ans.push_back(t);
    }
    return ans;
}
