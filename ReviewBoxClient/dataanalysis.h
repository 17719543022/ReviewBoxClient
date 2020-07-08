#ifndef DATAANALYSIS_H
#define DATAANALYSIS_H

#include <QObject>

class DataAnalysis : public QObject
{
    Q_OBJECT
public:
    explicit DataAnalysis(QObject *parent = nullptr);

    void updateVideoId(int videoId);

    void getVideoInfo();

    int width();

    int height();

signals:
    void newFrame_x(const QImage& image);

    void newFrame_s(const QImage& image);

public slots:

private:
    int videoId;

    long duration;

    double frameRate;

    int videoWidth;

    int videoHeight;
};

#endif // DATAANALYSIS_H
