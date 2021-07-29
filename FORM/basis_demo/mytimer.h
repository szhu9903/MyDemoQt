#ifndef MYTIMER_H
#define MYTIMER_H

#include <QTimer>
#include <QDateTime>
#include <QWidget>

namespace Ui {
class myTimer;
}

class myTimer : public QWidget
{
    Q_OBJECT

public:
    explicit myTimer(QWidget *parent = nullptr);
    ~myTimer();

//    void timerEvent(QTimerEvent *);

private:
    Ui::myTimer *ui;

    int id1, id2, id3;
    QTimer *timer;



private slots:
    void timerUpdate();

};

#endif // MYTIMER_H
