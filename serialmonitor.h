#ifndef SERIALMONITOR_H
#define SERIALMONITOR_H

#include "serialMonitor_global.h"
#include <QDebug>
#include <QSerialPort>
#include <QObject>
#include <QJsonDocument>
#include <QJsonObject>

class SERIALMONITOR_EXPORT SerialMonitor : public QObject
{
    Q_OBJECT
public:
    SerialMonitor();
    ~SerialMonitor();
private:
    QSerialPort * serialPort;
    QByteArray text;

private slots:
    void serialReceived();
signals:
    void readDoneSignal(QJsonObject);
};

#endif // SERIALMONITOR_H
