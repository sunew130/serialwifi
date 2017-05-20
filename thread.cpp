#include "thread.h"

Thread::Thread(QObject *parent) :
    QThread(parent)
{

    //struct PortSettings myComSetting = {BAUD38400,DATA_8,PAR_NONE,STOP_1,FLOW_OFF,500}; //38400 8N1 NONE
}

Thread::~Thread()
{
    isStop = true;
    MyCom->close();
}

//设置串口并打开
void Thread::openDevice(struct PortSettings com,QString deviceName,QString chName)
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
        isInit = false;
    }
}

/********************************
 ********************************
 *********获取数据********
 ********************************
 ********************************/
//读取pc端的数据
void Thread::run()
{
    QByteArray temp;
    while(isInit = true)
    {
        temp = MyCom->readAll();
        if(!temp.isEmpty())
        {
            if(temp.at(0) != 'A')
            {
                 if(temp.at(0) != 'U')
                 {
                     if(temp.at(0) != 'L')
                     {
                        if(temp.at(0) != 'h')
                        {

              if(!strcmp(temp.right(9),QByteArray("SEND OK\r\r")))
              {

                  qDebug()<<"REV:"<<temp;
                  emit sendcmddata(temp);
               }
              for(int i=0;i<temp.count();i++)
              {
                  if(temp.at(i) == ':')
                    {
                   QByteArray megtemp;
                    megtemp = temp.right(temp.count()-i-1).left(temp.count()-i-7);
                    qDebug()<<"REV:"<<megtemp;
                    emit sendcmddata(megtemp);
                   }

              }
                temp.clear();
                        }
                     }
                 }
            }


        }
    }

}

//写入数据
void Thread::writeData(QByteArray data)
{
    //qDebug()<<"write"<<data;

    if(data.size() != MyCom->write(data))
    {
        qDebug()<<tr("send error!");
    }
    else
    {
        //qDebug()<<data;
    }
}


/*
"AT+CWMODE=2\r\n";//设置成路由模式
"AT+CWSAP='ESP8266','0123456789',11,0\r\n";//设置路由
"AT+RST\r\n";//重启设备
"AT+CIPMUX=1\r\n";//启用多连接
"AT+CIPSERVER=1,5000\r\n";//设置服务器端口
"AT+CIPSEND=\r\n";//AT+CIPSEND= 发送数据
AT+CIPCLOSE //关闭tcp/udp连接
AT+CIFSR  //获取本地IP地址
AT+CIPSTO=10  //设置 TCP 服务器超时时间
AT+PING //测试网络地址
AT+CIOBAUD  /设置串口配置

AT+CWMODE=1 Station 模式
          2 AP 模式
          3 AP 兼 Station 模式

AT+CWLAP //列出当前可用 AP
AT+ CWJAP =“abc”,“0123456789” //加入热点AP
AT+CWQAP //退出与 AP 的连接

*/


void Thread::wifiInit()
{
   // writeData(QByteArray("\r\n"));
    qDebug()<<"begin init";
   // sleep(1);

    //AT+CWMODE=2 设置成路由模式
    writeData(QByteArray("AT+CWMODE=2\r\n"));

    sleep(1);
    //AT+CWSAP="ESP8266","0123456789",11,0 设置路由
   // writeData(QByteArray("AT+CWSAP='ESP8266','0123456789',11,0\r\n"));
    //sleep(3);

    //AT+RST 重启
    //writeData(QByteArray("AT+RST\r\n"));
    //sleep(5);

    //AT+CIPMUX=1 设置成多连接
    writeData(QByteArray("AT+CIPMUX=1\r\n"));
    sleep(2);

    //AT+CIPSERVER=1,5000 开启TCP服务端口
    writeData(QByteArray("AT+CIPSERVER=1,5000\r\n"));

    qDebug()<<"finish init";
    isInit =true;
}


void Thread::serverChat()
{
    char sbuf[20];
    QByteArray buf;
    while(1)
    {
        gets(sbuf);
        writeData(QByteArray("AT+CIPSEND=0,20\r\n"));
        // sleep(2);
        buf.append(sbuf);
        writeData(buf+QByteArray("                    \r\n"));
        bzero(sbuf, 20);
        buf.clear();
    }

}

void Thread::comeBack(QByteArray data)
{
    char num[10];
    if(data.data() != NULL)
    {

    sprintf(num,"%d\r\n",data.count()+2);
   // qDebug()<<QByteArray("AT+CIPSEND=0,").append(num);
    writeData(QByteArray("AT+CIPSEND=0,").append(num));

    writeData(data+QByteArray("\r\n"));
     qDebug()<<"OK!!";
   }


}


