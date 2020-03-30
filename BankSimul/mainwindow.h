#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_pushButton_nosta_clicked();

    void on_pushButton_talleta_clicked();

    void on_pushButton_tiedot_clicked();

    void on_pushButton_takaisin_1_clicked();

    void on_pushButton_takaisin_2_clicked();

    void on_pushButton_takaisin_3_clicked();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
