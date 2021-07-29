#include "FORM/mainwindow.h"
#include "FORM/logindialog.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    // 访问验证窗口
    LoginDialog login;
    if (login.exec() == QDialog::Accepted)
    {
        w.show();
        return a.exec();
    }
    else return 0;
}
