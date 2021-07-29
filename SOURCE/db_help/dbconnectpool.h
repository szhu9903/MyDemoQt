#ifndef DBCONNECTPOOL_H
#define DBCONNECTPOOL_H

#include <QObject>
#include <qlist.h>
#include <QSqlError>
#include "dbconnect.h"
#include <QMutex>


class DbConnectPool : public QObject
{
    Q_OBJECT
public:
    explicit DbConnectPool(QObject *parent = nullptr);

    QList<DbConnect *> DbPool;

    DbConnect * get_db_connect(QString db_name);
signals:

public slots:
    void executeSql(QString sql, QString db_name, bool &execute_flag);


};

#endif // DBCONNECTPOOL_H
