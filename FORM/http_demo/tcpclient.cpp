#include "tcpclient.h"
#include "ui_tcpclient.h"

TcpClient::TcpClient(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::TcpClient)
{
    ui->setupUi(this);
    tcpSocket = new QTcpSocket(this);
    connect(tcpSocket, SIGNAL(readyRead()), this, SLOT(readMessage()));
    connect(tcpSocket, SIGNAL(error(QAbstractSocket::SocketError)), this, SLOT(displayError(QAbstractSocket::SocketError)));
}

TcpClient::~TcpClient()
{
    delete ui;
}

// 创建连接
void TcpClient::newConnect()
{
    clockSize = 0;
    tcpSocket->abort(); //取消已有连接
    // 创建连接
    tcpSocket->connectToHost(ui->hostEdit->text(),ui->portEdit->text().toInt());
}

// 连接
void TcpClient::on_connButton_clicked()
{
    newConnect();
}

// 收到数据处理
void TcpClient::readMessage()
{
    QDataStream in(tcpSocket);
    if (clockSize == 0) // 刚开始接收数据
    {
        // 读取的数据过去短，继续读取
        if(tcpSocket->bytesAvailable() < sizeof (quint16)) return;
        in >> clockSize;
    }
    if (tcpSocket->bytesAvailable() < clockSize) return; // 读取数据不完成
    in >> message;
    qDebug() << "data message" << message;
    ui->textBrowser->append(message);
}

// 错误处理
void TcpClient::displayError(QAbstractSocket::SocketError)
{
    ui->textBrowser->append(tcpSocket->errorString());
}