#include "logindialog.h"
#include "ui_logindialog.h"

LoginDialog::LoginDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::LoginDialog)
{
    ui->setupUi(this);
    setWindowTitle(tr("访问认证"));
    ui->name_edit->setPlaceholderText("admin");
    ui->pwd_edit->setPlaceholderText("admin");
}

LoginDialog::~LoginDialog()
{
    delete ui;
}

void LoginDialog::on_login_btn_clicked()
{
    const char name[] = "admin";
    const char pwd[] = "admin";
    // trimmed 去除QString 开始结尾
    if (ui->name_edit->text().trimmed() == name && ui->pwd_edit->text().trimmed() == pwd)
    {
        accept();
    }else{
        QMessageBox::warning(this, tr("警告"),
                             tr("user name or password error!"),
                             QMessageBox::Yes);
        ui->name_edit->clear(); //  清空输入框
        ui->pwd_edit->clear();
        ui->name_edit->setFocus(); // 光标定位到文本框
    }
}