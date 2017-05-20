#ifndef QPROCESSDATA_H
#define QPROCESSDATA_H

#include <QObject>
#include <QTimer>

#include "thread.h"
#include "thread2.h"
#include "thread3.h"
#include "thread4.h"
#include "thread5.h"

class QProcessData : public QObject
{
    Q_OBJECT
public:
    explicit QProcessData(QObject *parent = 0);

    ~QProcessData();

    void readOilSensor(void);
    void readParticleSensor(void);
    void sendSensor(void);
    void releaseSensor(void);
    //测试端口
   void pcPort(void);
   void showTest(void);


public slots:
    void sendSensorData(QByteArray);
    void sendParticleCmd(QByteArray);
    void revBuf(void);

public:
    Thread2 *oilSensor;
    Thread3 *particleSensor;
    Thread4 *pcSender;
    Thread5 *Test;
    //Thread *sendSensorData;
    Thread *sendSensors;
};

#endif // QPROCESSDATA_H
