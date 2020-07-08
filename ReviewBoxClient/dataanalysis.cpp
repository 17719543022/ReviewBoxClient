#include "dataanalysis.h"
#include "VideoDecodeImpl.h"
#include <QDebug>

DataAnalysis::DataAnalysis(QObject *parent)
    : QObject(parent)
    , videoId(0)
    , duration(0)
    , frameRate(0)
    , videoWidth(0)
    , videoHeight(0)

{

}

void DataAnalysis::updateVideoId(int videoId)
{
    this->videoId = videoId;
}

void DataAnalysis::getVideoInfo()
{
    videoDecodeGetVideoInfo(videoId, &duration, &frameRate, &videoWidth, &videoHeight);
}

int DataAnalysis::width()
{
    return videoWidth;
}

int DataAnalysis::height()
{
    return videoHeight;
}
