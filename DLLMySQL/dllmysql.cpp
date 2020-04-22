#include "dllmysql.h"

#include <QWidget>
#include <QApplication>
#include <QtWidgets>
#include <QDebug>
#include <QSqlQuery>
#include <QtSql>
#include <QSqlQueryModel>
#include <QSqlTableModel>

QSqlDatabase DLLMySQL::db;

DLLMySQL::DLLMySQL()
{

    if(createConnection())
        query = new QSqlQuery;
}

DLLMySQL::~DLLMySQL()
{
    delete query;
    query = nullptr;
}

bool DLLMySQL::createConnection()
{
    db = QSqlDatabase::addDatabase("QMYSQL");
    db.setHostName("mysli.oamk.fi");

    db.setDatabaseName("opisk_t9laju04");
    db.setUserName("t9laju04");
    db.setPassword("W45GNJgDGhwMX6YW");

    if (!db.open())
    {
        QMessageBox::critical(0, qApp -> tr("Cannot open database"),
        qApp -> tr("Unable to establish a database connection.\n"),
        QMessageBox::Cancel);
        qDebug() << "Yhteytta ei voitu muodostaa" << endl;

        return false;
    }

    return true;
}

bool DLLMySQL::verifyCardKey(QString key)
{
    query->prepare("SELECT * FROM Card WHERE card_id = :key");
    query->bindValue(":key", key);

    if(!query->exec())
        qDebug() << query->lastError().text();

    query->first();

    return (query->size() > 0);
}

QString DLLMySQL::verifyCardPin(QString key, QString pin)
{
    query->prepare("SELECT account_id FROM Card WHERE card_id = :key and pin = :pin");
    query->bindValue(":key", key);
    query->bindValue(":pin", pin);

    if(!query->exec())
        qDebug() << query->lastError().text();

    query->first();

    if(query->size() > 0)
        return query->value(0).toString();
    else
        return "ERROR";
}

QString DLLMySQL::getAccountData(QString accountId, SearchMode mode)
{
    QString returnValue;

    if(mode == name)
    {
        query->prepare("SELECT user_id FROM Account WHERE account_id = :account_id");
        query->bindValue(":account_id", accountId);
        query->exec();

        query->first();
        int userId = query->value(0).toInt();

        query->prepare("SELECT firstname, lastname FROM User WHERE user_id = :user_id");
        query->bindValue(":user_id", userId);
        query->exec();

        query->first();

        returnValue = query->value(0).toString() + " " + query->value(1).toString();
    }
    else if(mode == saldo)
    {
        query->prepare("SELECT saldo FROM Account WHERE account_id = :account_id");
        query->bindValue(":account_id", accountId);
        query->exec();

        query->first();

        returnValue = query->value(0).toString();
    }
    else if(mode == activity)
    {
        query->prepare("SELECT description FROM Activity WHERE account_id = :account_id");
        query->bindValue(":account_id", accountId);
        query->exec();

        query->last();

        returnValue = "";

        do
            returnValue += query->value(0).toString() + "\n\n";
        while(query->previous());
    }

    return returnValue;
}

bool DLLMySQL::editSaldo(QString accountId, int amount)
{
    if(amount == 0 || (amount < 0 && -amount > getAccountData(accountId, saldo).toFloat()))
        return false;

    query->prepare("UPDATE Account SET saldo = saldo + :amount WHERE account_id = :account_id");
    query->bindValue(":amount", amount);
    query->bindValue(":account_id", accountId);

    if(!query->exec())
        return false;
    else
    {
        addActivity(accountId, amount);

        return true;
    }
}

void DLLMySQL::addActivity(QString accountId, int amount)
{
    QString activity = QDateTime().currentDateTime().toString("dd.MM.yyyy HH:mm") + " - ";

    if(amount < 0)
        activity += "Nosto: " + QString().setNum(-amount) + " €";
    else
        activity += "Talletus: " + QString().setNum(amount) + " €";

    query->exec("SELECT activity_id FROM Activity;");

    query->last();
    int nextId = query->size();

    // Lisää uusi tapahtuma
    query->prepare("INSERT INTO Activity VALUES(:activity_id, :account_Id, :activity);");
    query->bindValue(":activity_id", nextId);
    query->bindValue(":account_Id", accountId);
    query->bindValue(":activity", activity);

    query->exec();
}

/*
QString DLLMySQL::naytaSaldo(QString pinkoodi)
{
    QSqlQuery query;
    query.prepare("SELECT account_id FROM Card WHERE pin = :pin");
    query.bindValue(":pin", pinkoodi);

    if(!query.exec())
        qDebug() << query.lastError().text();

    query.first();

    return query.value(0).toString();
}
*/
