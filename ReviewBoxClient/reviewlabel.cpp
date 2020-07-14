#include "reviewlabel.h"
#include <QDebug>

ReviewLabel::ReviewLabel(QWidget *parent) : QLabel(parent)
{

}

void ReviewLabel::onNewResultFrame(int result0, int result1, int result2, int result3, int result4, int result5, QString boxStr)
{
    Q_UNUSED(boxStr)

    this->result[0] = result0;
    this->result[1] = result1;
    this->result[2] = result2;
    this->result[3] = result3;
    this->result[4] = result4;
    this->result[5] = result5;

    update();
}

void ReviewLabel::paintEvent(QPaintEvent *event)
{
    QLabel::paintEvent(event);

    QPainter painter;
    painter.begin(this);

    if (result[4] == 0) {
        painter.setPen(QPen(Qt::green, 1, Qt::SolidLine, Qt::RoundCap));
    } else {
        painter.setPen(QPen(Qt::red, 1, Qt::SolidLine, Qt::RoundCap));
    }
    painter.drawRect(QRect(result[0], result[1], result[2], result[3]));

    painter.end();
}
