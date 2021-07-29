#ifndef TCPCLIENT_H
#define TCPCLIENT_H

#include <QWidget>
#include <QtNetwork>
#include <QDebug>

namespace Ui {
class TcpClient;
}

class TcpClient : public QWidget
{
    Q_OBJECT

public:
    explicit TcpClient(QWidget *parent = nullptr);
    ~TcpClient();

private:
    Ui::TcpClient *ui;

    QTcpSocket *tcpSocket;
    QString message; // 存放接收到的数据
    quint16 clockSize; // 文件大小信息

private slots:
    void on_connButton_clicked();
    void newConnect();
    void readMessage();
    void displayError(QAbstractSocket::SocketError);

};

#endif // TCPCLIENT_H
