#include "serialportengine.h"

SerialPortEngine::SerialPortEngine(QObject *parent) : QObject(parent)
{
    serial = new QSerialPort(this);
    serial->setPortName("COM3");
    serial->setBaudRate(QSerialPort::Baud9600);
    serial->setDataBits(QSerialPort::Data8);
    serial->setParity(QSerialPort::NoParity);
    serial->setStopBits(QSerialPort::OneStop);
    serial->setFlowControl(QSerialPort::NoFlowControl);
    // serial->setFlowControl(QSerialPort::HardwareControl);

    connect(serial, SIGNAL(readyRead()), this, SLOT(receiveSerial()));
}

SerialPortEngine::~SerialPortEngine()
{
    serial->close();

    delete serial;
    serial = nullptr;
}

void SerialPortEngine::openConnection()
{
    serial->open(QIODevice::ReadOnly);

    if(serial->open(QIODevice::ReadOnly))
    {
        qDebug() << "Serial ei auki";
        return;
    }

    serial->clear(QSerialPort::AllDirections);
}

void SerialPortEngine::receiveSerial()
{
    byteArray = serial->readAll();

    keyString = QTextCodec::codecForMib(106)->toUnicode(byteArray);

    emit sendKey(keyString);
}
