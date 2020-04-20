#ifndef DLLPINCODE_H
#define DLLPINCODE_H

#include <QWidget>
#include "DLLPinCode_global.h"
#include "dialog.h"

class DLLPINCODE_EXPORT DLLPinCode : public QWidget
{
public:
    DLLPinCode();
    ~DLLPinCode();


private:
    Dialog *objectDLLPinCodeEngine;

private slots:
    void receivePin(QString);


signals:
    void returnPin(QString);
};



#endif // DLLPINCODE_H
