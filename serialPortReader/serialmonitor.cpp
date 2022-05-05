#include "serialmonitor.h"

SerialMonitor::SerialMonitor()
{
    serialPort = new QSerialPort();

    connect(serialPort, SIGNAL(readyRead()), this, SLOT(serialReceived()));

    settings = new QSettings("settings.ini", QSettings::IniFormat);
    settings->sync();

    readSettingsFile();
}

SerialMonitor::~SerialMonitor()
{
    disconnect(serialPort, SIGNAL(readyRead()), this, SLOT(serialReceived()));
    serialPort->close();

    delete settings;
    settings = nullptr;
    delete serialPort;
    serialPort = nullptr;
}

void SerialMonitor::initSerialPort(QString comPort)
{

    serialPort->setPortName(comPort);

    serialPort->setBaudRate(QSerialPort::Baud115200);
    serialPort->setDataBits(QSerialPort::Data8);
    serialPort->setParity(QSerialPort::NoParity);
    serialPort->setStopBits(QSerialPort::OneStop);
    serialPort->setFlowControl(QSerialPort::NoFlowControl);
    serialPort->open(QIODevice::ReadOnly);

    if(serialPort->isOpen()){
        qDebug() << "Port:" << port << "is open";

    }else{

        qDebug() << "Error on opening port:" << serialPort->error();
        qDebug() << "Configure settings.ini file with correct port";
        qDebug() << "or reconnect the USB";
    }
}

void SerialMonitor::readSettingsFile()
{
    settings->beginGroup("SerialReader");

    port = settings->value("port", "None").toString();
    qDebug() << "Using port:" << port;

    settings->endGroup();

    initSerialPort(port);
}

void SerialMonitor::serialReceived()
{
    if(serialPort->readLine() == ""){
        return;
    }

    text += serialPort->readLine();

    if(text.contains("\r\n")){

        QJsonDocument doc = QJsonDocument::fromJson(text);

        qDebug() << doc;

        text = "";
        QJsonObject data = doc.object();

        emit readDoneSignal(data);
    }
}
