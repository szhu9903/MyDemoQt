#ifndef SQLDIALOG_H
#define SQLDIALOG_H

#include <QDialog>
#include <QString>

namespace Ui {
class SqlDialog;
}

class SqlDialog : public QDialog
{
    Q_OBJECT

public:
    explicit SqlDialog(QWidget *parent = nullptr);
    ~SqlDialog();

    QString host, port, name, pwd, database;

private:
    Ui::SqlDialog *ui;

signals:
    void conn_database();

private slots:
    void on_connButton_clicked();

};

#endif // SQLDIALOG_H
