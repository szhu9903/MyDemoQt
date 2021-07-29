#ifndef DBCONNECT_H
#define DBCONNECT_H

#include <QObject>
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include <QDebug>

class DbConnect: public QObject
{
    Q_OBJECT
public:
    explicit DbConnect(QObject *parent = 0);

    QSqlDatabase db;
    QString db_connectname;

signals:

public slots:
    bool ExecuteSql(QString sql);

};

#endif // DBCONNECT_H
