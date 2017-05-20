#include "thread5.h"

Thread5::Thread5(QObject *parent) :
    QThread(parent)
{

    //struct PortSettings myComSetting = {BAUD38400,DATA_8,PAR_NONE,STOP_1,FLOW_OFF,500}; //38400 8N1 NONE
}

Thread5::~Thread5()
{
    isStop = true;
    MyCom->close();
}

//设置串口并打开
void Thread5::openDevice(struct PortSettings com,QString deviceName,QString chName)
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
void Thread5::run()
{
    char sbuf[20];
    QByteArray buf;
    while(1)
    {
    gets(sbuf);
    buf.append(sbuf);

   MyCom->write(buf);
    bzero(sbuf, 20);
    buf.clear();
    }


}





void Thread5::serverChat()
{
        QByteArray temp;
        QByteArray temp0;
      //  while(!isStop)
     //  {

            temp = MyCom->readAll();

            temp0 = temp.toHex();
          // qDebug()<<"jishuqi"<<temp;

            //MyCom->write(temp);


            if(!temp.isEmpty())
            {

                qDebug()<<"SHOWTEST:"<<temp;

                //MyCom->write(QByteArray("has rev!!!"));
//                if(temp0.size() == 72)
                //{

                 //   emit senddata(QByteArray("oil") + temp0 + QByteArray("\r\n"));
//                }
               // temp.clear();
            }

        //   emit senddata(QByteArray("oil") + QByteArray("\r\n"));

      //  }





}








