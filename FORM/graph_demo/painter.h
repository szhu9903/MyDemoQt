#ifndef PAINTER_H
#define PAINTER_H

#include <QWidget>

namespace Ui {
class Painter;
}

class Painter : public QWidget
{
    Q_OBJECT

public:
    explicit Painter(QWidget *parent = nullptr);
    ~Painter();

private:
    Ui::Painter *ui;

protected:
    void paintEvent(QPaintEvent *);

};

#endif // PAINTER_H
