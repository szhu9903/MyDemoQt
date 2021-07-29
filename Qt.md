## Qt5 mac

### 数据库操作
1. 创建数据库连接
``` C++
    db_name = "demo_conn"; // 连接名称：数据库连接池区分不同连接
    dbConnect = QSqlDatabase::addDatabase("QMYSQL", db_name); // 数据库驱动，需要自行编译 
    dbConnect.setHostName("localhost");
    dbConnect.setPort(3306);
    dbConnect.setUserName("root");
    dbConnect.setPassword("db_pwd");
    dbConnect.setDatabaseName("qt_test");
    if (dbConnect->db.open())
    {
        qDebug() << "conn success!";
    } else
    {
        qDebug() << "conn error!" << dbConnect->db.lastError().text();
    }
    QSqlQuery query(dbConnect->db);
    if(query.exec("select * from table_name"))
    {
        while (query.next())
        {
            QString data = query.value(0).toString() + "-" + query.value(1).toString() + "-" + query.value(2).toString();
            qDebug() << "查询数据成功" << data;
        }
    }else
    {
        qDebug() << query.lastError();
    }
```
* 操作结果集  
  > previous() ：query指向上一条记录，每执行一次该函数，便指向相邻的上一条记录；  
  > next(): query指向下一条记录，每执行一次该函数，便指向相邻的下一条记录；  
  > first(): query指向结果集的第一条记录；  
  > last(): query指向结果集的最后一条记录；  
  > seek(int n): query指向结果集的第n条；  
  > record() ：获得现在指向的记录；  
  > value(int n) ：获得属性的值。其中n表示你查询的第n个属性  
  > at() ：获得现在query指向的记录在结果集中的编号。
* 事务
  > QSqlDatabase::transaction():来启动一个事务  
  > QSqlDatabase::commit():提交  
  > QSqlDatabase::rollback():回滚