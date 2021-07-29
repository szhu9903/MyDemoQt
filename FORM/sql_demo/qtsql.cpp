#include "qtsql.h"
#include "ui_qtsql.h"


QtSql::QtSql(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::QtSql)
{
    ui->setupUi(this);
    setWindowTitle("SQL Window!");

    dbConnectPool = new DbConnectPool;
    connect(this, &QtSql::Execute_Sql, dbConnectPool, &DbConnectPool::executeSql, Qt::AutoConnection);
    sqlDialog = new SqlDialog;
//    connect(sqlDialog, &SqlDialog::conn_database, this, &QtSql::create_conn_database, Qt::AutoConnection);

}

QtSql::~QtSql()
{
    delete ui;
}


// 打开配置窗口
void QtSql::on_configButton_clicked()
{
    sqlDialog->show();
}

// 创建链接
void QtSql::on_createButton_clicked()
{
    dbConnect = dbConnectPool->get_db_connect("demo");
    qDebug() << "connection conn " << dbConnect->db;
    if (dbConnect->db.open())
    {
        ui->statusBrowser->setText("创建连接成功！");
    }else
    {
        ui->statusBrowser->setText("创建连接失败！");
    }

}

// 执行sql 语句
void QtSql::on_executeButton_clicked()
{
    QString sql = ui->sqlEdit->toPlainText();
    bool execute_flag = false;
    qDebug() << "重复调用bug";
    emit Execute_Sql(sql, "demo", execute_flag);
    if (execute_flag)
    {
        ui->statusBrowser->setText("执行成功！");
    }
}

// 查询语句
//select * from person, insert into person(name, age) values("szhu", 111)
void QtSql::on_queryButton_clicked()
{
    if (!dbConnect)
    {
        dbConnect = dbConnectPool->get_db_connect("demo");
    }
    QSqlQuery query(dbConnect->db);
    QString sql = ui->sqlEdit->toPlainText();
    if(query.exec(sql))
    {
        ui->statusBrowser->append("获取到数据 \n");
        while (query.next())
        {
            QString data = query.value(0).toString() + "-" + query.value(1).toString() + "-" + query.value(2).toString();
            ui->statusBrowser->append(data);
        }
    }else
    {
        qDebug() << query.lastError();
    }

}


