#include "thread4.h"

Thread4::Thread4(QObject *parent) :
    QThread(parent)
{

    //struct PortSettings myComSetting = {BAUD38400,DATA_8,PAR_NONE,STOP_1,FLOW_OFF,500}; //38400 8N1 NONE
}

Thread4::~Thread4()
{
    isStop = true;
    MyCom->close();
}

//设置串口并打开
void Thread4::openDevice(struct PortSettings com,QString deviceName,QString chName)
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
 *********获取数据********
 ********************************
 ********************************/
void Thread4::run()
{
     QByteArray temp;
    /*
    QByteArray temp;
    QByteArray temp0;
    while(!isStop)
    {

        temp = MyCom->readAll();
        temp0 = temp.toHex();
        qDebug()<<temp;

        //qDebug()<<temp0;

        if(!temp.isEmpty())
        {
            if(temp0.size() == 72)
            {

             //   emit senddata(QByteArray("oil") + temp0 + QByteArray("\r\n"));
            }
        }

    //   emit senddata(QByteArray("oil") + QByteArray("\r\n"));

    }
    */
  //  while(!isStop)
   // {

    while(!isStop)
    {

   // qDebug()<<"oil";
    MyCom->write(QByteArray("oil\n"));
    temp = MyCom->readAll();
   // if(!temp.isEmpty())
  //  {
    qDebug()<<"comeback:"<<temp;


   // }
    sleep(1);
   }

}
