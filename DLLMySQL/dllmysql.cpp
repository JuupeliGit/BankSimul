#include "dllmysql.h"
#include <QWidget>
#include <QApplication>
#include <QtWidgets>
#include <QDebug>
#include <QSqlQuery>
#include <QtSql>
#include <QSqlQueryModel>
#include <QSqlTableModel>


DLLMySQL::DLLMySQL()
{
    createConnection();
}

bool DLLMySQL::createConnection()
{
    qDebug() << "TESITITISI!";

    QSqlDatabase db = QSqlDatabase::addDatabase("QMYSQL");
    db.setHostName("mysli.oamk.fi");
    db.setDatabaseName("opisk_t9hejo01");
    db.setUserName("t9hejo01");
    db.setPassword("hnUd92L3ghqsBwuY");

    if (!db.open())
    {
        QMessageBox::critical(0, qApp -> tr("Cannot open database"),
        qApp -> tr("Unable to establish a database connection.\n"),
        QMessageBox::Cancel);
        qDebug() << "Yhteytta ei voitu muodostaa" << endl;
        return false;
    }
    else if (db.open())
    {
        qDebug() << "Yhteys muodostettu" << endl;
    }

    QSqlQuery query;
    query.exec("create table tili1(pin int primary key, "
               "firstname varchar(20), lastname(20), saldo varchar (10))");
    query.exec("insert into tili1 values(1000, 'Paavo', 'Routa', '1700')");
    query.exec("insert into tili1 values(1100, 'Laura', 'Haapala', '5100')");
    query.exec("insert into tili1 values(1200, 'Mauri', 'Kauppila', '4000')");
    query.exec("insert into tili1 values(1300, 'Risto', 'Väisänen', '8500')");
    query.exec("insert into tili1 values(1400, 'Marja', 'Galvan', '6000')");
    query.exec("insert into tili1 values(1500, 'Mikko', 'Mäki', '7000')");


    return true;
}

void DLLMySQL::getValuesFromModel(QSqlTableModel *model)
{
    model -> setTable("tili1");

    model -> setFilter("firstname = 'Mikko'");

    model -> select();

    QString pin = model -> data(model -> index(0,0)).toString();
    QString etu = model -> data(model -> index(0,1)).toString();
    QString suku = model -> data(model -> index(0,2)).toString();
    QString saldo = model -> data(model -> index(0,3)).toString();

    qDebug() << pin;
    qDebug() << etu;
    qDebug() << suku;
    qDebug() << saldo;

}

float DLLMySQL::naytaSaldo(int pinkoodi)
{
    QSqlQuery query;
    query.prepare("SELECT saldo FROM tili1 WHERE pin = :pin");
    query.bindValue(":pin", pinkoodi);
    query.exec();

    while (query.next())
    {
        QString tulos = query.value(0).toString();
        saldo = tulos.toFloat();
    }

    return saldo;
}
