#include "tcpsender.h"
#include "ui_tcpsender.h"

TcpSender::TcpSender(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::TcpSender),
    localSize(1024)

{
    ui->setupUi(this);
    totalBytes = 0;
    bytesWritten = 0;
    bytesTowrite = 0;
    fileKey.shortData = 0;
    ui->clientBar->reset();
    tcpClient = new QTcpSocket(this);
    // 当连接创建成功时，发出connected信号，开始发送文件
    connect(tcpClient, SIGNAL(connected()), this, SLOT(startTransfer()));
    // 有数据发送成功，更新进度条
    connect(tcpClient, SIGNAL(bytesWritten(qint64)), this, SLOT(updateClientProcess(qint64)));
    // 从缓冲区读取到数据
    connect(tcpClient, SIGNAL(readyRead()), this, SLOT(readData()));
    connect(tcpClient, SIGNAL(errorOccurred(QAbstractSocket::SocketError)), this, SLOT(displayError(QAbstractSocket::SocketError)));
    ui->sendButton->setEnabled(false);
}

TcpSender::~TcpSender()
{
    delete ui;
    tcpClient->close();
    delete tcpClient;
}

void TcpSender::openFile()
{
    fileName = QFileDialog::getOpenFileName();
    if(!fileName.isEmpty())
    {
        ui->sendButton->setEnabled(true);
        ui->statuslabel->setText(tr("打开文件 %1 成功").arg(fileName));
    }
}

void TcpSender::send()
{
    ui->sendButton->setEnabled(false);
    bytesWritten = 0;
    ui->statuslabel->setText("连接中！");
    tcpClient->connectToHost(ui->hostEdit->text(), ui->portEdit->text().toInt());
}

void TcpSender::startTransfer()
{
    localFile = new QFile(fileName);
    if (!localFile->open(QFile::ReadOnly))
    {
        qDebug() << "open file error!";
        return;
    }
    // 文件总大小
    totalBytes = localFile->size();

    QDataStream sendOut(&outBlock, QIODevice::WriteOnly);
    QString currentFileName = fileName.right(fileName.size()-fileName.lastIndexOf('/')-1);

    sendOut << qint8(1) << qint8(30) << qint8(1) << qint32(0);
    sendOut << qint64(totalBytes) << currentFileName.toUtf8();
    // 数据包长度
    qint32 send_data_len = outBlock.size() - sizeof (qint32) - sizeof (qint8) * 3;
    sendOut.device()->seek(3);
    sendOut << send_data_len;

    bytesTowrite = totalBytes;
    tcpClient->write(outBlock);
    ui->statuslabel->setText(tr("已连接"));
    outBlock.resize(0);
}

void TcpSender::updateClientProcess(qint64 numBytes)
{
    qDebug() << "send data" << numBytes;
}

void TcpSender::readData()
{
    QByteArray data = tcpClient->readAll();
    qDebug() << "获取响应数据";
    if (!qint8(data[0]))
        qDebug() << "保存数据失败";
    if (fileKey.shortData == 0)
    {
        // 栈存储
        fileKey.dataBytes[1] = (quint8) data[1];
        fileKey.dataBytes[0] = (quint8) data[2];
        qDebug() << fileKey.shortData;
    }
    if(bytesTowrite > 0)
    {
        qDebug() << bytesTowrite << bytesTowrite;
        QDataStream sendOut(&outBlock, QIODevice::WriteOnly);
        sendOut << qint8(1) << qint8(30) << qint8(2) << qint32(0);
        sendOut << qint16(fileKey.shortData) << localFile->read(qMin(bytesTowrite, localSize));
        // 数据包长度
        qint32 data_len = outBlock.size() - sizeof(qint32) - sizeof(qint8) * 3;
        sendOut.device()->seek(sizeof (qint8) * 3);
        sendOut << data_len;

        tcpClient->write(outBlock);
        //发送完一次数据后还剩余数据的大小:实际文件大小
        bytesWritten += data_len - sizeof(qint16) - 4;
        bytesTowrite -= data_len - sizeof(qint16) - 4;

        //清空发送缓冲区
        outBlock.resize(0);
    }else{
        localFile->close();
    }
    //更新进度条
    ui->clientBar->setMaximum(totalBytes);
    ui->clientBar->setValue(bytesWritten);

    if(bytesWritten == totalBytes)
    {
        ui->statuslabel->setText("发送完成");
        fileKey.shortData = 0;
        localFile->close();
        tcpClient->close();
    }
}

void TcpSender::displayError(QAbstractSocket::SocketError)
{
    qDebug() << tcpClient->errorString();
    tcpClient->close();
    ui->clientBar->reset();
    ui->statuslabel->setText("准备就绪");
    ui->sendButton->setEnabled(true);
}

void TcpSender::on_openButton_clicked()
{
    openFile();
}

void TcpSender::on_sendButton_clicked()
{
    send();
}