#include "popupdialog.h"
#include "ui_popupdialog.h"

PopUpDialog::PopUpDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::PopUpDialog)
{
    ui->setupUi(this);


}

void PopUpDialog::avaa(PopUpMode mode)
{
    if(mode == nosto)
    {
        ui->stackedWidget->setCurrentIndex(0);
        ui->label_onnistui->setText("Nosto onnistui!");
    }
    else if(mode == talletus)
    {
        ui->stackedWidget->setCurrentIndex(0);
        ui->label_onnistui->setText("Talletus onnistui!");
    }
    else
        ui->stackedWidget->setCurrentIndex(1);

    this->show();
}

PopUpDialog::~PopUpDialog()
{
    delete ui;
}

void PopUpDialog::on_pushButton_etusivu_clicked()
{
    emit siirryEtusivu();
    this->close();
}

void PopUpDialog::on_pushButton_tiedot_clicked()
{
    emit siirryTiedot();
    this->close();
}

void PopUpDialog::on_pushButton_ok_clicked()
{
    this->close();
}
