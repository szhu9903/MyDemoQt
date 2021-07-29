#include "mytimer.h"
#include "ui_mytimer.h"

myTimer::myTimer(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::myTimer)
{
    ui->setupUi(this);
    id1 = startTimer(1000);
    id2 = startTimer(2000);
    id3 = startTimer(10000);

    timer = new QTimer();
    connect(timer, &QTimer::timeout, this, &myTimer::timerUpdate, Qt::AutoConnection);
    timer->start(3000);

}

myTimer::~myTimer()
{
    delete ui;
}

//// 定时器时间，检测各个定时器溢出，做对应的操作程序
//void myTimer::timerEvent(QTimerEvent *event)
//{
//    // timerID() 返回溢出的定时器ID
//    if (event->timerId() == id1)
//    {
//        ui->label->setText(tr("%1").arg(qrand()%10));
//    } else if (event->timerId() == id2)
//    {
//        ui->label_2->setText(tr("Hello"));
//    }else
//    {
//        qApp->quit();
//    }
//
//}
void myTimer::timerUpdate()
{
    // 当前系统时间
    QDateTime time = QDateTime::currentDateTime();
    // 格式化时间
    QString str = tr("%1,%2").arg(qrand()%10).arg(time.toString("yyyy-MM-DD hh:mm:ss dddd"));
    // 显示时间
    ui->label->setText(str);
}

