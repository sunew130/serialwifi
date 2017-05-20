#include "thread3.h"

Thread3::Thread3(QObject *parent) :
    QThread(parent)
{

    //struct PortSettings myComSetting = {BAUD38400,DATA_8,PAR_NONE,STOP_1,FLOW_OFF,500}; //38400 8N1 NONE
}

Thread3::~Thread3()
{
    isStop = true;
    MyCom->close();
}

//设置串口并打开
void Thread3::openDevice(struct PortSettings com,QString deviceName,QString chName)
{
    MyCom = new Posix_QextSerialPort(deviceName,com,QextSerialBase::Polling); //串口2

    bool temp;
    temp = MyCom->open(QIODevice::ReadWrite); //打开串口设备
    if(temp < 0)
    {
        qDebug()<<tr("open device error!\n");
    }
    else
    {
        channelName = chName;
        isStop = false;
    }
}

/********************************
 ********************************
 *********获取数据****************
 ********************************
 ********************************/
//读取颗粒计数器数据，转发到串口1
void Thread3::run()
{

    QByteArray temp;
    while(!isStop)
    {
        temp = MyCom->readAll();
        // qDebug()<<"port3:"<<temp;
        //temp0 = temp.toHex();
        if(!temp.isEmpty())
        {
            // qDebug()<<"port3:"<<temp;
            //MyCom->write(temp);
            //emit senddata(QByteArray("par") + temp + QByteArray("\n"));
            // writeData(temp);
            emit senddata(temp);
            temp.clear();
        }
    }

}


//发送数据到颗粒计数器
void Thread3::writeData(QByteArray data)
{
    // qDebug()<<"2:"<<data;
    qDebug()<<MyCom->write(data.data());

}
