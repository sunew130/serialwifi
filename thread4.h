#ifndef THREAD4_H
#define THREAD4_H

#include <QObject>
#include <QThread>
#include <QtDebug>

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <termios.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <strings.h>
#include <math.h>

#include "posix_qextserialport.h"
#include "qextserialbase.h"
#include "qextserialport.h"

class Thread4 : public QThread
{
    Q_OBJECT
public:
    Thread4(QObject *parent = 0);
    ~Thread4();

    //设置串口并打开
    void openDevice(struct PortSettings com,QString deviceName,QString chName);

    bool isStop;
    QString channelName;

protected:
    virtual void run();

signals:
    void senddata(QByteArray);

private:
    Posix_QextSerialPort *MyCom;

};

#endif // THREAD4_H
