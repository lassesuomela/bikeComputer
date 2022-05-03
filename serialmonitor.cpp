#include "serialmonitor.h"

SerialMonitor::SerialMonitor()
{
    serialPort = new QSerialPort();

    serialPort->setPortName("com4");

    serialPort->setBaudRate(QSerialPort::Baud115200);
    serialPort->setDataBits(QSerialPort::Data8);
    serialPort->setParity(QSerialPort::NoParity);
    serialPort->setStopBits(QSerialPort::OneStop);
    serialPort->setFlowControl(QSerialPort::NoFlowControl);
    serialPort->open(QIODevice::ReadOnly);

    connect(serialPort, SIGNAL(readyRead()), this, SLOT(serialReceived()));
}

SerialMonitor::~SerialMonitor()
{
    serialPort->close();
    delete serialPort;
    serialPort = nullptr;
}

void SerialMonitor::serialReceived()
{
    text += serialPort->readLine();

    if(text.contains("\r\n")){

        QJsonDocument doc = QJsonDocument::fromJson(text);
        text = "";
        QJsonObject data = doc.object();

        emit readDoneSignal(data);
    }
}
