#include "dbconnect.h"

DbConnect::DbConnect(QObject *parent) : QObject(parent)
{

}

bool DbConnect::ExecuteSql(QString sql)
{
    if (db.isOpen())
    {
        QSqlQuery query(db);
        query.prepare(sql); // 定义动态可占位符:id、:name，
//        query.addBindValue();// 然后替换占位符
        if (query.exec())
        {
            qDebug() << "执行成功";
            return true;
        }else
        {
            qDebug() << query.lastError();
            return false;
        }
    }
}

