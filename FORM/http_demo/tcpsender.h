#ifndef TCPSENDER_H
#define TCPSENDER_H

#include <QWidget>
#include <QFile>
#include <QtNetwork>
#include <QFileDialog>
#include <QDebug>

typedef union {
    quint16 shortData;
    quint8 dataBytes[2];
} shortDataType1;


namespace Ui {
class TcpSender;
}

class TcpSender : public QWidget
{
    Q_OBJECT

public:
    explicit TcpSender(QWidget *parent = nullptr);
    ~TcpSender();

private:
    Ui::TcpSender *ui;

    QTcpSocket * tcpClient;
    QFile *localFile; // 要发送的文件
    qint64 totalBytes; // 数据总大小
    qint64 bytesWritten; // 已发送数据大小
    qint64 bytesTowrite; // 剩余文件大小
    const qint64 localSize; // 每次要发送的文件大小
    QString fileName;   // 保存文件路径
    QByteArray outBlock; // 数据缓冲区，存放每次要发送的数据

    shortDataType1 fileKey;

private slots:
    void send(); // 连接服务器
    void startTransfer(); // 发送文件大小等信息
    void updateClientProcess(qint64); // 发送数据，更新进度条
    void readData();
    void displayError(QAbstractSocket::SocketError); // 显示错误信息
    void openFile(); //打开文件
    void on_openButton_clicked();
    void on_sendButton_clicked();
};

#endif // TCPSENDER_H
