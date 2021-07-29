#ifndef QTSQL_H
#define QTSQL_H

#include <QWidget>
#include <QDebug>
#include "sqldialog.h"
#include "SOURCE/db_help/dbconnectpool.h"
#include "SOURCE/db_help/dbconnect.h"


namespace Ui {
class QtSql;
}

class QtSql : public QWidget
{
    Q_OBJECT

public:
    explicit QtSql(QWidget *parent = nullptr);
    ~QtSql();

private:
    Ui::QtSql *ui;

    DbConnectPool *dbConnectPool;
    DbConnect *dbConnect;
    SqlDialog *sqlDialog;

signals:
    void Execute_Sql(QString sql, QString db_name, bool &execute_flag);

private slots:
    void on_configButton_clicked();
    void on_createButton_clicked();
    void on_executeButton_clicked();
    void on_queryButton_clicked();

};

#endif // QTSQL_H
