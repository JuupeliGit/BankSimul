#include "dllserialport.h"

DLLSerialPort::DLLSerialPort()
{
    qDebug() << "DLLSerialPort constructor";

    serialEngine = new SerialPortEngine();
    connect(serialEngine, SIGNAL(sendKey(QString)), this, SLOT(receiveKey(QString)));

    emit returnKey("testi avain");

    serialEngine->openConnection();
}

DLLSerialPort::~DLLSerialPort()
{
    delete serialEngine;
    serialEngine = nullptr;
}

void DLLSerialPort::receiveKey(QString keyString)
{
    emit returnKey(keyString);
}
