#include "sqldialog.h"
#include "ui_sqldialog.h"


SqlDialog::SqlDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SqlDialog)
{
    ui->setupUi(this);
}

SqlDialog::~SqlDialog()
{
    delete ui;
}

void SqlDialog::on_connButton_clicked()
{
    host = ui->hostEdit->text().trimmed();
    port = ui->portEdit->text().trimmed();
    name = ui->nameEdit->text().trimmed();
    pwd = ui->pwdEdit->text().trimmed();
    database = ui->databaseEdit->text().trimmed();
    emit conn_database();

}

