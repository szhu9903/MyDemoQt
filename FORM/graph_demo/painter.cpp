#include "painter.h"
#include "ui_painter.h"
#include <QPainter>

Painter::Painter(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Painter)
{
    ui->setupUi(this);
}

Painter::~Painter()
{
    delete ui;
}

void Painter::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    painter.drawLine(QPointF(0, 0), QPointF(100, 100));
}