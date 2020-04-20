#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    objectMySQL = new DLLMySQL;

    objectSerialPort = new DLLSerialPort;
    connect(objectSerialPort, SIGNAL(returnKey(QString)), this, SLOT(getKeyFromSerial(QString)));

    objectPinCode = new DLLPinCode;
    connect(objectPinCode, SIGNAL(returnPin(QString)), this, SLOT(getPin(QString)));
}

MainWindow::~MainWindow()
{
    delete ui;

    delete objectSerialPort;
    objectSerialPort = nullptr;

    delete objectPinCode;
    objectPinCode = nullptr;

    delete objectMySQL;
    objectMySQL = nullptr;
}


void MainWindow::getKeyFromSerial(QString key)
{
    qDebug() << key;

    objectPinCode->openDialog();
}

void MainWindow::getPin(QString pin)
{
    qDebug() << pin;

    qDebug() << objectMySQL->naytaSaldo(pin.toInt());

    if(ui->stackedWidget->currentIndex() == 0)
        ui->stackedWidget->setCurrentIndex(1);
}


void MainWindow::on_pushButton_nosta_clicked()
{
    ui->stackedWidget->setCurrentIndex(2);
}

void MainWindow::on_pushButton_talleta_clicked()
{
    ui->stackedWidget->setCurrentIndex(3);
}

void MainWindow::on_pushButton_tiedot_clicked()
{
    ui->stackedWidget->setCurrentIndex(4);
}

void MainWindow::on_pushButton_takaisin_1_clicked()
{
    ui->stackedWidget->setCurrentIndex(1);
}

void MainWindow::on_pushButton_takaisin_2_clicked()
{
    ui->stackedWidget->setCurrentIndex(1);
}

void MainWindow::on_pushButton_takaisin_3_clicked()
{
    ui->stackedWidget->setCurrentIndex(1);
}

void MainWindow::on_pushButton_kirjauduUlos_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);
}

void MainWindow::on_pushButton_skipKortti_clicked()
{
    getKeyFromSerial("05009B2FE2");
}
