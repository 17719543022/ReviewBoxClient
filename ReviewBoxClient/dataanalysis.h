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
    void newFrameX(const QImage& image);

    void newFrameS(const QImage& image);

    void stateCameraXChange(bool state);

    void stateCameraSChange(bool state);

    void newResultFrame(int result0, int result1, int result2, int result3, int result4, int result5, QString boxStr);

private:
    int videoId;

    long duration;

    double frameRate;

    int videoWidth;

    int videoHeight;
};

#endif // DATAANALYSIS_H
