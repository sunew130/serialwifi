#ifndef THREAD2_H
#define THREAD2_H

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

class Thread2 : public QThread
{
    Q_OBJECT
public:
    Thread2(QObject *parent = 0);
    ~Thread2();

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

#endif // THREAD2_H
