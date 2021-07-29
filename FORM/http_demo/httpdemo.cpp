#include "httpdemo.h"
#include "ui_httpdemo.h"

HttpDemo::HttpDemo(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::HttpDemo) {
    ui->setupUi(this);
    manager = new QNetworkAccessManager(this); // 用来发送网络请求和接收应答。
    ui->requestBar->hide();
}

HttpDemo::~HttpDemo()
{
    delete ui;
}

void HttpDemo::startRequest(QUrl url)
{
    replay = manager->get(QNetworkRequest(url));
    connect(replay, &QNetworkReply::readyRead, this, &HttpDemo::httpReadyRead);
    connect(replay, &QNetworkReply::downloadProgress, this, &HttpDemo::updateDataReadProgress);
    connect(replay, &QNetworkReply::finished, this, &HttpDemo::httpFinished);
}

void HttpDemo::on_requestButton_clicked()
{
    url = ui->urlEdit->text();
    startRequest(url);
    ui->requestBar->setValue(0);
    ui->requestBar->show();
}

// 当有新数据的时候
void HttpDemo::httpReadyRead()
{
    QTextCodec *codec = QTextCodec::codecForName("utf-8");
    QString all = codec->toUnicode(replay->readAll());
    ui->textBrowser->setText(all);
}

//  更新进度条 设置最大值，当前值
void HttpDemo::updateDataReadProgress(qint64 bytesReceived, qint64 bytesTotal)
{
    ui->requestBar->setMaximum(bytesTotal);
    ui->requestBar->setValue(bytesReceived);
}

//  接收完成 删除replay
void HttpDemo::httpFinished()
{
    ui->requestBar->hide();
    replay->deleteLater();
    replay = 0;
}

