#ifndef SERIALMONITOR_H
#define SERIALMONITOR_H

#include "serialMonitor_global.h"
#include <QDebug>
#include <QSerialPort>
#include <QObject>
#include <QJsonDocument>
#include <QJsonObject>
#include <QSettings>

class SERIALMONITOR_EXPORT SerialMonitor : public QObject
{
    Q_OBJECT
public:
    SerialMonitor();
    ~SerialMonitor();
private:
    QSerialPort * serialPort;
    QByteArray text;
    QSettings * settings;
    QString port;

    void initSerialPort(QString);
    void readSettingsFile();

private slots:
    void serialReceived();
signals:
    void readDoneSignal(QJsonObject);
    void serialPortErrSignal();
};

#endif // SERIALMONITOR_H
