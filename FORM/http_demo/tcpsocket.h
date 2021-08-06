#ifndef TCPSOCKET_H
#define TCPSOCKET_H

#include <QWidget>
#include <QtNetwork>
#include <QDebug>
#include <QList>

typedef union {
    quint16 shortData;
    quint8 dataBytes[2];
} shortDataType;

typedef union {
    float floatData;
    quint8 dataBytes[4];
} floatDataType;


namespace Ui {
class TcpSocket;
}

class TcpSocket : public QWidget
{
    // 宏，使用信号和槽必须加入这个宏
    Q_OBJECT

public:
    explicit TcpSocket(QWidget *parent = nullptr);
    ~TcpSocket();

    QList<QHostAddress> hostList;
    QString getIp();
    void set_str(QByteArray & block, QString & data_str);

private:
    Ui::TcpSocket *ui; //指针ui,对象

    QTcpServer *tcpServer;
    qint8 blogLen;
    shortDataType length;
    shortDataType id;
    shortDataType age;
    floatDataType number;

private slots:
    void connMessage();

};

#endif // TCPSOCKET_H
