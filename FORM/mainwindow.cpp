#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QLabel>
#include <QKeyEvent>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
//    ui->statusbar->showMessage(tr("Hello admin!"), 5000);
    statusLabel = new QLabel;
    statusLabel->setMinimumSize(150, 20); //设置最小大小
    statusLabel->setFrameShape(QFrame::WinPanel);
    statusLabel->setFrameShadow(QFrame::Sunken);
    ui->statusbar->addWidget(statusLabel);
    statusLabel->setText("Hello admin!");
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_fileButton_clicked()
{
    fileWindow = new FileWindow;
    fileWindow -> show();
}

void MainWindow::on_timerButton_clicked()
{
    MyTimer = new myTimer;
    MyTimer -> show();
}

void  MainWindow::on_painterButton_clicked()
{
    painter = new Painter;
    painter->show();
}

void MainWindow::on_sqlButton_clicked()
{
    qtSql = new QtSql();
    qtSql->show();
}

void MainWindow::on_httpButton_clicked()
{
    http = new HttpDemo;
    http->show();
}

void MainWindow::on_tcpButton_clicked()
{
    tcpSocket = new TcpSocket;
    tcpSocket->show();
}

void MainWindow::on_clientButton_clicked()
{
    tcpClient = new TcpClient;
    tcpClient->show();
}



