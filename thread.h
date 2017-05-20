#ifndef THREAD_H
#define THREAD_H

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

//struct PortSettings com = {BAUD38400,DATA_8,PAR_NONE,STOP_1,FLOW_OFF,500};

class Thread : public QThread
{
    Q_OBJECT
public:
    Thread(QObject *parent = 0);
    ~Thread();

    void writeData(QByteArray);

    //设置串口并打开
    void openDevice(struct PortSettings com,QString deviceName,QString chName);

    //初始wifi模块
    void wifiInit();

    //服务器回复
    void serverChat();

    //回复应答
    void comeBack(QByteArray data);

    bool isStop;
    QString channelName;

protected:
    virtual void run();

signals:
    void sendcmddata(QByteArray);

private:
    bool isInit;
    Posix_QextSerialPort *MyCom;

};

#endif // THREAD_H
