#include "streamcamera.h"

StreamCamera::StreamCamera(QString ipAddress, quint16 port, QString fileName, QObject *parent)
    : CameraModel(parent), ipAddr(ipAddress), port(port), fileName(fileName)
{
    camera_type = STREAM;
    source_type = STREAM_ENVI;
}

bool StreamCamera::start() {
    frame_width = 640;
    frame_height = 480;
    data_height = 480;

    framesize = frame_width * frame_height;

    dummy.resize(size_t(framesize));
    std::fill(dummy.begin(), dummy.end(), 0);

    // Magic numbers!
    circBuf = CircBuffer<QVector<uint16_t>>(96);

    return true;
}

StreamCamera::~StreamCamera()
{
    running.store(false);
}

/* Didn't get around to making a proper 'Go!' button
 * so the camera activates when the user tries to
 * open a file */
void StreamCamera::setDir(const char *filename)
{
    tcpSocket = new QTcpSocket();
    connect(tcpSocket, &QIODevice::readyRead, this, &StreamCamera::tcpReadyRead);

    // This needs to be reimplemented but for TCP reading
    //
    // Close out the last file stream
    //if (is_reading) {
    //    is_reading = false;
    //    readLoopFuture.waitForFinished();
    //}

    tcpSocket->connectToHost(ipAddr, port);
    if (!tcpSocket->isOpen()) {
        qDebug("Could not open socket.");
        if (running.load()) {
            running.store(false);
            emit timeout();
            return;
        }
    }
    running.store(true);
}

/*
 * Slot that activates when there is data waiting to be read from
 * the TCP socket
*/
void StreamCamera::tcpReadyRead()
{
    // Read all available data from socket
    inBuffer.append(tcpSocket->readAll());

    // If there are enough bytes to get a full frame, read
    // from the buffer
    while (inBuffer.size() >= framesize * int(sizeof(uint16_t))) {
        QFile file("test.envi");
        file.open(QIODevice::WriteOnly);
        QDataStream testOut(&file);

        // Since the network data uses BigEndian, we must use
        // QDataStream to convert back to LittleEndian when reading
        // integers
        QDataStream pixStream(&inBuffer, QIODevice::ReadOnly);
        QVector<uint16_t> frame;
        for (int i=0; i < framesize; i++) {
            uint16_t pix;
            pixStream >> pix;
            testOut << pix;
            frame.append(uint16_t(pix));
        }
        inBuffer.remove(0, framesize * sizeof(uint16_t));

        circBuf.add(frame);
        file.close();
    }
}

uint16_t* StreamCamera::getFrame()
{
    /*
    if(!frame_buf.empty() && running.load()) {
        std::vector<uint16_t> temp_frame = frame_buf.back();
        frame_buf.pop_back();
        return temp_frame.data();
    }*/
    if(circBuf.count() != 0 && running.load()) {
        QVector<uint16_t> tempFrame = circBuf.pop();
        return tempFrame.data();
    }
    else {
        return dummy.data();
    }
}
