#ifndef STREAMCAMERA_H
#define STREAMCAMERA_H

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
#include <QTcpSocket>
#include <QHostAddress>

#include "cameramodel.h"
#include "constants.h"
#include "lvframe.h"
#include "osutils.h"
#include "envicamera.h"
#include "circbuffer.h"

class StreamCamera : public CameraModel
{
    Q_OBJECT

public:
    StreamCamera(QString ipAddress = "127.0.0.1",
                 quint16 port = 1234,
                 QString fileName = "ROICDATA.raw",
                 QObject *parent = nullptr);

    ~StreamCamera();

    virtual uint16_t *getFrame();
    virtual void setDir(const char *filename);
    virtual bool start();

private slots:
    void tcpReadyRead();

private:
    // TCP Socket where we read data
    QTcpSocket* tcpSocket = nullptr;

    // Socket information
    QString ipAddr;
    quint16 port;
    QString fileName;

    /* Buffer where TCP data is stored until enough
     * bytes are accumulated to create one full
     * frame
    */
    QByteArray inBuffer;

    // Number of pixels in a frame
    int framesize;

    /* Ring buffer where frames that have arrived through TCP are
     * stored while waiting to be processsed
    */
    QVector< std::vector<uint16_t> > frame_buf;

    CircBuffer<QVector<uint16_t>> circBuf;

    // Dummy frame to send when there is no real data
    std::vector<uint16_t> dummy;
};

#endif // STREAMCAMERA_H
