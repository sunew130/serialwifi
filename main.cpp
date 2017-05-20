#include <QCoreApplication>
#include <QtDebug>
//#include "thread.h";
#include "qprocessdata.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    QProcessData *dataProcess;
    dataProcess = new QProcessData();
    //qDebug()<<"hello";
    return a.exec();
}

