#include "qprocessdata.h"

QProcessData::QProcessData(QObject *parent) :
    QObject(parent)
{
    //this->readOilSensor();
    
    // sleep(1);
    
    this->readParticleSensor();
    
    //sleep(1);
    

    
    //sleep(1);
    //this->pcPort();
    
    this->showTest();

    this->sendSensor();
   //Test->serverChat();
    QTimer *qtimer =new QTimer(this);
    connect(qtimer,SIGNAL(timeout()),this,SLOT(revBuf()));
    qtimer->start(1000);
}

QProcessData::~QProcessData()
{
    this->releaseSensor();
}



void QProcessData::revBuf(void)
{

    Test->serverChat();
}











//定义四合一传感器串口
void QProcessData::readOilSensor(void)
{
    struct PortSettings myComSetting = {BAUD38400,DATA_8,PAR_NONE,STOP_1,FLOW_OFF,500};//BAUD38400
    oilSensor = new Thread2(this);
    oilSensor->openDevice(myComSetting,tr("/dev/ttyUSB0"),tr("oil-sensor"));
    oilSensor->start();
    connect(oilSensor,SIGNAL(senddata(QByteArray)),this,SLOT(sendSensorData(QByteArray)));
}


//定义颗粒计数器串口
void QProcessData::readParticleSensor(void)
{
    struct PortSettings myComSetting = {BAUD115200,DATA_8,PAR_NONE,STOP_1,FLOW_OFF,500};
    particleSensor = new Thread3(this);
    particleSensor->openDevice(myComSetting,tr("/dev/ttyUSB1"),tr("particle-sensor"));
    particleSensor->start();
    // QThread::sleep(10);
    connect(particleSensor,SIGNAL(senddata(QByteArray)),this,SLOT(sendSensorData(QByteArray)),Qt::QueuedConnection);
    
    //QTimer *timerP = new QTimer(this);
    //connect(timerP,SIGNAL(timeout()),this,SLOT(sendParticleCmd()));
    //timerP->start(10000);
}


//定义颗粒计数器发送指令
void QProcessData::sendParticleCmd(QByteArray cmd)
{
    //qDebug()<<tr("send cmd")<<cmd;
    //QByteArray cmd = QByteArray("ok");
    //qDebug()<<cmd<<QByteArray("keli");
    //qDebug()<<"show:"<<cmd;
    particleSensor->writeData(cmd);
}


//定义发送串口设备
void QProcessData::sendSensor(void)
{
    struct PortSettings myComSetting = {BAUD115200,DATA_8,PAR_NONE,STOP_1,FLOW_OFF,500};
    sendSensors = new Thread(this);
    sendSensors->openDevice(myComSetting,tr("/dev/ttyUSB0"),tr("cmd"));//dev/ttySAC1
    sendSensors->start();
    // QThread::sleep(10);
    sendSensors->wifiInit();
    connect(sendSensors,SIGNAL(sendcmddata(QByteArray)),this,SLOT(sendParticleCmd(QByteArray)),Qt::QueuedConnection);//,Qt::QueuedConnection
    //connect()
}


//发送传感器数据
void QProcessData::sendSensorData(QByteArray data)
{
    //qDebug()<<tr("send ")<<data;
   //  qDebug()<<"port3:"<<data;
    sendSensors->comeBack(data);
}


//pc端
void QProcessData::pcPort(void)
{
    struct PortSettings myComSetting = {BAUD115200,DATA_8,PAR_NONE,STOP_1,FLOW_OFF,500};
    pcSender = new Thread4(this);
    pcSender->openDevice(myComSetting,tr("/dev/ttyS0"),tr("cmd"));
    pcSender->start();
}


//计数器模拟
void QProcessData::showTest(void)
{
    struct PortSettings myComSetting = {BAUD115200,DATA_8,PAR_NONE,STOP_1,FLOW_OFF,500};
    Test = new Thread5(this);
    Test->openDevice(myComSetting,tr("/dev/ttyUSB2"),tr("particle-sensor"));
    Test->start();

}



//释放设备
void QProcessData::releaseSensor()
{
    //delete oilSensor;
    delete particleSensor;
    delete sendSensors;
    // delete pcSender;
    delete Test;
}
