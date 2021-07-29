#ifndef HTTPDEMO_H
#define HTTPDEMO_H

#include <QWidget>
#include <QtNetwork>
#include <QTextCodec>

namespace Ui {
class HttpDemo;
}

class HttpDemo : public QWidget
{
    Q_OBJECT

public:
    explicit HttpDemo(QWidget *parent = nullptr);
    ~HttpDemo();

    void startRequest(QUrl url);

private:
    Ui::HttpDemo *ui;
    QNetworkAccessManager *manager;
    QFile *file;
    QUrl url;
    QNetworkReply *replay;

private slots:
    void on_requestButton_clicked();
    void httpReadyRead();
    void httpFinished();
    void updateDataReadProgress(qint64, qint64);

};

#endif // HTTPDEMO_H
