#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "FORM/logindialog.h"
#include "FORM/basis_demo/filewindow.h"
#include "FORM/basis_demo/mytimer.h"
#include "FORM/graph_demo/painter.h"
#include "FORM/http_demo/httpdemo.h"
#include "FORM/sql_demo/qtsql.h"
#include "FORM/http_demo/tcpsocket.h"
#include "FORM/http_demo/tcpclient.h"
#include "FORM/http_demo/tcpsender.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class QLabel;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    FileWindow *fileWindow;
    myTimer *MyTimer;
    Painter *painter;
    QtSql *qtSql;
    HttpDemo *http;
    TcpSocket *tcpSocket;
    TcpClient *tcpClient;
    TcpSender *tcpSender;

private:
    Ui::MainWindow *ui;
    QLabel *statusLabel;

private slots:
    void on_fileButton_clicked();
    void on_timerButton_clicked();
    void on_painterButton_clicked();
    void on_sqlButton_clicked();
    void on_httpButton_clicked();
    void on_tcpButton_clicked();
    void on_clientButton_clicked();
    void on_sendFileButton_clicked();

};
#endif // MAINWINDOW_H
