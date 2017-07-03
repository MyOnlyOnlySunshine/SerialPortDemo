#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include<QSerialPort>
#include <QSerialPortInfo>
#include <QTimer>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    QStringList _baudL;
    QStringList _parityL;
    QStringList _stopL;
    QStringList _dataL;
    QStringList _flowControlL;
    QSerialPort  *serialPort;
    QTimer * timer;
    QTimer *scanTimer;


private slots:
    void on_pushButton_clicked(bool checked);
    void on_pushButton_2_clicked();
    void recievedData();
    void  scanSerialPort();


    void on_pushButton_3_clicked();

    void on_pushButton_4_clicked();

private:
    Ui::MainWindow *ui;
    void  configPort();
    void  setDefaultData();
    void reFreshUI();
    void enableOrDisableSomeButtons(bool enabled);
    void setupSerialPort();
    void setupTimer();
    void setupScanTimer();

};

#endif // MAINWINDOW_H
