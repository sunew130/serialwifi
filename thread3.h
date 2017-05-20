#ifndef THREAD3_H
#define THREAD3_H

#include <QObject>
#include <QtDebug>
#include <QThread>

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

class Thread3 : public QThread
{
    Q_OBJECT
public:
    Thread3(QObject *parent = 0);
    ~Thread3();



    //设置串口并打开
    void openDevice(struct PortSettings com,QString deviceName,QString chName);

    bool isStop;
    QString channelName;

    void writeData(QByteArray);

protected:
    virtual void run();

signals:
    void senddata(QByteArray);

private:
    Posix_QextSerialPort *MyCom;
    
};

#endif // THREAD3_H
