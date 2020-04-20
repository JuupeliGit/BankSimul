#include "dllpincode.h"
#include "ui_dialog.h"
#include <QDesktopWidget>

DLLPinCode::DLLPinCode()
{
   objectDLLPinCodeEngine = new Dialog;
   QObject::connect(objectDLLPinCodeEngine, &Dialog::sendPin, this, &DLLPinCode::receivePin);

}

DLLPinCode::~DLLPinCode()
{
    delete objectDLLPinCodeEngine;
    objectDLLPinCodeEngine = nullptr;
}

void DLLPinCode::receivePin(QString receivedPin)
{
    emit returnPin(receivedPin);
}
