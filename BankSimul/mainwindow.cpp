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

    objectPopUpDialog = new PopUpDialog;
    connect(objectPopUpDialog, SIGNAL(siirryEtusivu()), this, SLOT(on_pushButton_takaisin_1_clicked()));
    connect(objectPopUpDialog, SIGNAL(siirryTiedot()), this, SLOT(on_pushButton_tiedot_clicked()));

    cardKey = "";
    accountId = "";

    ui->lineEdit_maara_nosto->setValidator(new QIntValidator(20, 1000, this));
    ui->lineEdit_maara_talletus->setValidator(new QIntValidator(5, 1000, this));
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

    delete objectPopUpDialog;
    objectPopUpDialog = nullptr;
}


void MainWindow::setAccountData()
{
   ui->label_tervetuloa->setText("Tervetuloa " + objectMySQL->getAccountData(accountId, name));
   ui->label_saldo->setText("Saldo: " + objectMySQL->getAccountData(accountId, saldo));

   ui->textBrowser_tapahtumat->setText(objectMySQL->getAccountData(accountId, activity));
}

void MainWindow::getKeyFromSerial(QString key)
{
    cardKey = key;

    if(objectMySQL->verifyCardKey(cardKey))
        objectPinCode->toggleDialog(true);
}

void MainWindow::getPin(QString pin)
{
    accountId = objectMySQL->verifyCardPin(cardKey, pin);

    if(accountId != "ERROR")
    {
        objectPinCode->toggleDialog(false);

        if(ui->stackedWidget->currentIndex() == 0)
        {
            setAccountData();
            ui->stackedWidget->setCurrentIndex(1);
        }
    }
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
    accountId = "";
    ui->stackedWidget->setCurrentIndex(0);
}

void MainWindow::on_pushButton_skipKortti_clicked()
{
    getKeyFromSerial(ui->lineEdit_skip->text());
}

void MainWindow::withdraw(int amount)
{
    if(objectMySQL->editSaldo(accountId, -amount))
    {
        setAccountData();
        objectPopUpDialog->avaa(nosto);
    }
    else
        objectPopUpDialog->avaa(epaonnistui);

    ui->lineEdit_maara_nosto->setText("");
}

void MainWindow::on_pushButton_hyvaksy_talletus_clicked()
{
    int amount = ui->lineEdit_maara_talletus->text().toInt();

    if(objectMySQL->editSaldo(accountId, amount))
    {
        setAccountData();
        objectPopUpDialog->avaa(talletus);
    }
    else
        objectPopUpDialog->avaa(epaonnistui);

    ui->lineEdit_maara_talletus->setText("");
}

void MainWindow::on_pushButton_nosta_20_clicked()
{
    withdraw(20);
}

void MainWindow::on_pushButton_nosta_50_clicked()
{
    withdraw(50);
}

void MainWindow::on_pushButton_nosta_100_clicked()
{
    withdraw(100);
}

void MainWindow::on_pushButton_nosta_150_clicked()
{
    withdraw(150);
}

void MainWindow::on_pushButton_nosta_200_clicked()
{
    withdraw(200);
}

void MainWindow::on_pushButton_nosta_250_clicked()
{
    withdraw(250);
}
