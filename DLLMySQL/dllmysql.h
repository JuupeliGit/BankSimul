#ifndef DLLMYSQL_H
#define DLLMYSQL_H

#include "DLLMySQL_global.h"
#include <QMessageBox>
#include <QApplication>
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include <QDebug>
#include <QSqlQueryModel>
#include <QtWidgets>
#include <QWidget>
#include <QSqlTableModel>
#include <QtSql>
#include <QString>



class DLLMySQL : public QObject
{
    Q_OBJECT

public:
    DLLMySQL();

    static bool createConnection();
    void getValuesFromModel(QSqlTableModel *model);
    float naytaSaldo(int pinKoodi);

private:
    float saldo;
};

#endif // DLLMYSQL_H
