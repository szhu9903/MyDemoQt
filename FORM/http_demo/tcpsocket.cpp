#include "tcpsocket.h"
#include "ui_tcpsocket.h"

TcpSocket::TcpSocket(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::TcpSocket)
{
    ui->setupUi(this);
    tcpServer = new QTcpServer(this);
    if(!tcpServer->listen(QHostAddress::LocalHost, 6666))
    {
        qDebug() << "服务端启动失败" << tcpServer->errorString();
        close();
    }
    connect(tcpServer, SIGNAL(newConnection()), this, SLOT(connMessage()), Qt::AutoConnection);
}

TcpSocket::~TcpSocket()
{
    delete ui;
}

QString TcpSocket::getIp()
{
    QString ip = 0;
    hostList = QNetworkInterface::allAddresses();
    foreach(QHostAddress address, hostList)
    {
        if(address.protocol() == QAbstractSocket::IPv4Protocol)
            ip = address.toString();
    }
    return ip;
}

void TcpSocket::set_str(QByteArray &block, QString &data_str)
{
    block.append(data_str.toUtf8());
    block.append('\0');
    blogLen += (data_str.toUtf8().size() + 1);
}

void TcpSocket::connMessage()
{
    // 临时存储要发送的数据
    QByteArray block;
    QString data_str;
    //ID
    blogLen = 0;
    this->id.shortData = 1312;
    block[0] = char(id.dataBytes[1]);
    block[1] = char(id.dataBytes[0]);
    // name
    data_str = "朱测试空间占位";
    set_str(block, data_str);
    // age
    qDebug() << blogLen + 2  << "数据长度";
    this->age.shortData = 22;
    block[2+blogLen] = char(age.dataBytes[1]);
    block[3+blogLen] = char(age.dataBytes[0]);
    // address
    data_str = "河南省许昌市";
    set_str(block, data_str);
    // number
    this->number.floatData = 159.23;
    block[4+blogLen] = number.dataBytes[3];
    block[5+blogLen] = number.dataBytes[2];
    block[6+blogLen] = number.dataBytes[1];
    block[7+blogLen] = number.dataBytes[0];
    //长度
    qDebug() << blogLen + 8  << "数据长度";
    this->length.shortData = 8 + blogLen;
    block.insert(0, length.dataBytes[0]);
    block.insert(0, length.dataBytes[1]);

    QTcpSocket *clientConnection = tcpServer->nextPendingConnection(); // 服务端 获取已建立连接的TCP套接字
    connect(clientConnection, SIGNAL(disconnected()), clientConnection, SLOT(deleteLater()));
    clientConnection->write(block); //发送链接
    clientConnection->disconnectFromHost(); // 发送完成断开链接，发出disconnected信号，然后调用deleteLater确保关闭连接后删除套接字clientConnection
    // 提示
    ui->connBrowser->setText("响应完成");

}
