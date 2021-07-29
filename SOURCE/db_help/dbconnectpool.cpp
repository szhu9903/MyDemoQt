#include "dbconnectpool.h"

DbConnectPool::DbConnectPool(QObject *parent) : QObject(parent)
{
}

//从数据库连接池获取数据库连接，获取不到则创建新数据库连接
DbConnect* DbConnectPool::get_db_connect(QString db_name)
{
    QMutex mutex;
    mutex.lock();
    DbConnect *dbConnect = NULL;
    for(int i = 0; i < DbPool.size(); i++)
    {
        // 存在有效连接
        if (DbPool[i]->db_connectname == db_name && DbPool[i]->db.open())
        {
            dbConnect = DbPool[i];
            qDebug() << "获取数据库连接成功";
            break;
        }
    }
//     连接池还没有需要的有效连接，创建新连接
    if (dbConnect == NULL)
    {
        dbConnect = new DbConnect;
        dbConnect->db_connectname = db_name;
        dbConnect->db = QSqlDatabase::addDatabase("QMYSQL", db_name);
        dbConnect->db.setHostName("localhost");
        dbConnect->db.setPort(3306);
        dbConnect->db.setUserName("root");
        dbConnect->db.setPassword("szhu9903");
        dbConnect->db.setDatabaseName("qt_test");
        if (dbConnect->db.open())
        {
            qDebug() << "conn success!";

            DbPool.append(dbConnect);
            qDebug() << "append success!";
        } else
        {
            qDebug() << "conn error!" << dbConnect->db.lastError().text();
        }
    }
    mutex.unlock();
    return dbConnect;
}

// 提交数据
void DbConnectPool::executeSql(QString sql, QString db_name, bool &execute_flag)
{
    DbConnect * dbConnect = get_db_connect(db_name);
    dbConnect->db.transaction(); // 开启事务
    execute_flag = dbConnect->ExecuteSql(sql);
    if(execute_flag)
    {
        dbConnect->db.commit(); // 提交事务
    }else
    {
        dbConnect->db.rollback(); // 回滚
    }
}

