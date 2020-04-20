#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    objectSerialPort = new DLLSerialPort;
    connect(objectSerialPort, SIGNAL(returnKey(QString)), this, SLOT(getKeyFromSerial(QString)));
}

MainWindow::~MainWindow()
{
    delete ui;

    delete objectSerialPort;
    objectSerialPort = nullptr;
}


void MainWindow::getKeyFromSerial(QString key)
{
    qDebug() << key;
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
