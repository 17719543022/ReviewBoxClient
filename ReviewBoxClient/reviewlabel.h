#ifndef REVIEWLABEL_H
#define REVIEWLABEL_H

#include <QLabel>
#include <QPainter>

class ReviewLabel : public QLabel
{
    Q_OBJECT

public:
    ReviewLabel(QWidget *parent = nullptr);

protected:
    void paintEvent(QPaintEvent *) override;

public slots:
    void onNewResultFrame(int result0, int result1, int result2, int result3, int result4, int result5);

private:
    int result[6];
};

#endif // REVIEWLABEL_H
