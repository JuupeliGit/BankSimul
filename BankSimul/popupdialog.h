#ifndef POPUPDIALOG_H
#define POPUPDIALOG_H

#include <QDialog>

namespace Ui {
class PopUpDialog;
}

enum PopUpMode
{
    nosto,
    talletus,
    epaonnistui
};

class PopUpDialog : public QDialog
{
    Q_OBJECT

public:
    explicit PopUpDialog(QWidget *parent = nullptr);
    ~PopUpDialog();
    void avaa(PopUpMode mode);

private slots:
    void on_pushButton_etusivu_clicked();

    void on_pushButton_tiedot_clicked();

    void on_pushButton_ok_clicked();

signals:
    void siirryEtusivu();
    void siirryTiedot();

private:
    Ui::PopUpDialog *ui;
};

#endif // POPUPDIALOG_H
