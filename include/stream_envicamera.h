#ifndef STREAM_ENVICAMERA_H
#define STREAM_ENVICAMERA_H

#include <array>
#include <deque>
#include <fstream>
#include <vector>
#include <sstream>
#include <string>

#include <QtConcurrent/QtConcurrent>
#include <QCoreApplication>
#include <QDebug>
#include <QFuture>
#include <QTime>

#include "cameramodel.h"
#include "constants.h"
#include "lvframe.h"
#include "osutils.h"
#include "envicamera.h"

class Stream_ENVICamera : public CameraModel
{
    Q_OBJECT

public:
    Stream_ENVICamera(int frWidth = 640,
               int frHeight = 480,
               int dataHeight = 480,
               QObject *parent = nullptr);
    ~Stream_ENVICamera();

    virtual uint16_t *getFrame();
    virtual void setDir(const char *filename);

private:
    bool readHeader(std::string hdrname);
    ENVIData HDRData;
    void readLoop();

    bool is_reading; // Flag that is true while reading from a directory
    std::ifstream dev_p;
    std::string ifname;
    std::string hdrname;
    std::streampos bufsize;
    const int framesize;
    std::deque< std::vector<uint16_t> > frame_buf;
    std::vector<uint16_t> dummy;
    std::vector<uint16_t> temp_frame;
    int curIndex;
    int nFrames;
    int chunkFrames; // frames to read per buffered chunk
    int framesRead;

    QFuture<void> readLoopFuture;
    int tmoutPeriod;
};

#endif // STREAM_ENVICAMERA_H
