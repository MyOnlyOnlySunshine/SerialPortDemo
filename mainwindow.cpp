#include "mainwindow.h"
#include "ui_mainwindow.h"
#include<QDebug>
#include<QMessageBox>
#include<QSerialPort>
#include<QSerialPortInfo>
#include<QList>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setupScanTimer();
    setDefaultData();
}

MainWindow::~MainWindow()
{
    delete ui;
    delete serialPort;
    delete timer;
    delete  scanTimer;
}

void MainWindow::configPort()
{
    ui->comboBox->clear();

   foreach(const QSerialPortInfo &portInfo,QSerialPortInfo::availablePorts())
   {
       QString portName = portInfo.portName();

           if(portName.startsWith("cu") &&  !portName.endsWith("Port"))
           {
               ui->comboBox->addItem(portInfo.portName());
               // qDebug()<<"pro"<<portInfo.productIdentifier()<<"\n"<<"vendor"<<portInfo.vendorIdentifier();
            }
   }
}
void MainWindow::setDefaultData()
{
     QList<QStringList >strList;
      _baudL<<"1200"<<"2400"<<"4800"<<"9600"<<"19200"<<"38400"<<"57600"<<"115200"<<"-1";
      _dataL<<"5"<<"6"<<"7"<<"8"<<"-1";
      _parityL<<"0"<<"2"<<"3"<<"4"<<"5"<<"-1";
      _stopL<<"1"<<"1.5"<<"2"<<"-1";
      _flowControlL<<"0"<<"1"<<"2"<<"-1";
       strList<<_baudL<<_dataL<<_parityL<<_stopL<<_flowControlL;

      QList<QComboBox *>  boxList;
      boxList<<ui->comboBox_2<<ui->comboBox_3<<ui->comboBox_4<<ui->comboBox_5<<ui->comboBox_6;

      for(int i= 0;i<strList.count();i++)
      {
        // qDebug()<<"boxList"<<boxList<<"\n"<<"strList"<<strList<<endl;
         boxList[i] ->addItems(strList[i]);
         switch(i)
         {
             case 0:
                 boxList[i]->setCurrentIndex(7);
                 break;
             case 1:
                 boxList[i]->setCurrentIndex(3);
                 break;
         }
      }
     ui->pushButton_2->setEnabled(false);
}

void MainWindow::enableOrDisableSomeButtons(bool enabled)
{
       if(ui->pushButton->text() == "关闭串口")
       {
           ui->pushButton ->setText("打开串口");
           ui->pushButton->setStyleSheet("QPushButton {color: black;}");
           enabled = true;
       }
       else
      {
           ui->pushButton->setText("关闭串口");
           ui->pushButton->setStyleSheet("QPushButton {color: white; }");
           enabled = false;
      }

         ui->pushButton_2->setEnabled(enabled);
         ui->comboBox->setEnabled(enabled);
         ui->comboBox_2->setEnabled(enabled);
         ui->comboBox_3->setEnabled(enabled);
         ui->comboBox_4->setEnabled(enabled);
         ui->comboBox_5->setEnabled(enabled);
         ui->comboBox_6->setEnabled(enabled);
}

void MainWindow::setupSerialPort()
{
    serialPort = new QSerialPort(this);
    serialPort->setPortName(ui->comboBox->currentText());
    if(serialPort->open(QIODevice::ReadOnly))
    {
         enableOrDisableSomeButtons(true);
         ui->pushButton_2->setEnabled(true);
         serialPort->setBaudRate(ui->comboBox_2->currentText().toInt());

    switch(ui->comboBox_3->currentIndex())
    {
      case 0:
    {
         serialPort->setDataBits(QSerialPort::Data5) ;
        break;
    }
    case 1:
    {
         serialPort->setDataBits(QSerialPort::Data6) ;
       break;
    }
    case 2:
    {
         serialPort->setDataBits(QSerialPort::Data7) ;
        break;
    }
    case 3:
    {
         serialPort->setDataBits(QSerialPort::Data8) ;
        break;
    }
  case 4:
    {
         serialPort->setDataBits(QSerialPort::UnknownDataBits) ;
        break;
    }
    default:
        serialPort->setDataBits(QSerialPort::Data8) ;
        break;

    }
    switch(ui->comboBox_4->currentIndex())
    {
      case 0:
    {
         serialPort->setParity(QSerialPort::NoParity) ;
        break;
    }
    case 1:
    {
         serialPort->setParity(QSerialPort::EvenParity) ;
       break;
    }
    case 2:
    {
         serialPort->setParity(QSerialPort::OddParity) ;
        break;
    }
    case 3:
    {
         serialPort->setParity(QSerialPort::SpaceParity) ;
        break;
    }
  case 4:
    {
         serialPort->setParity(QSerialPort::MarkParity) ;
        break;
    }
    case 5:
      {
           serialPort->setParity(QSerialPort::UnknownParity) ;
          break;
      }
    default:
        serialPort->setParity(QSerialPort::NoParity) ;
        break;

    }
    switch(ui->comboBox_5->currentIndex())
    {
      case 0:
    {
         serialPort->setStopBits(QSerialPort::OneStop) ;
        break;
    }
    case 1:
    {
         serialPort->setStopBits(QSerialPort::OneAndHalfStop) ;
       break;
    }
    case 2:
    {
         serialPort->setStopBits(QSerialPort::TwoStop) ;
        break;
    }
    case 3:
    {
         serialPort->setStopBits(QSerialPort::UnknownStopBits) ;
        break;
    }

    default:
        serialPort->setStopBits(QSerialPort::OneStop) ;
        break;
    }
    switch(ui->comboBox_5->currentIndex())
    {
      case 0:
    {
         serialPort->setFlowControl(QSerialPort::NoFlowControl) ;
        break;
    }
    case 1:
    {
         serialPort->setFlowControl(QSerialPort::HardwareControl) ;
       break;
    }
    case 2:
    {
         serialPort->setFlowControl(QSerialPort::SoftwareControl) ;
        break;
    }
    case 3:
    {
         serialPort->setFlowControl(QSerialPort::UnknownFlowControl) ;
        break;
    }

    default:
        serialPort->setFlowControl(QSerialPort::NoFlowControl) ;
        break;
    }
   }
//    else if(serialPort->open(QIODevice::ReadOnly))
//    {
//        ui->pushButton_2->setEnabled(true);
//        QMessageBox::warning(this,"警告","串口只读");
//    }
    else
    {
        ui->pushButton_2->setEnabled(false);
        qDebug()<<"error"<<serialPort->errorString();
        QMessageBox::critical(this,"错误","请打开串口");
    }
}
void MainWindow::setupTimer()
{
    timer = new  QTimer(this);
    connect(serialPort,SIGNAL(readyRead()),this,SLOT(recievedData()));
   // timer->start(500);
}

void MainWindow::setupScanTimer()
{
     scanTimer = new QTimer(this);
     connect(scanTimer,SIGNAL(timeout()),this,SLOT(scanSerialPort()));
     scanTimer->start(1000);
}

void MainWindow ::scanSerialPort()
{
    configPort();
}

void MainWindow::recievedData()
{
    QByteArray readData = serialPort->readAll();
    if(readData.length()>0)
    {
        qDebug()<<"recieved data"<<readData;
        ui->plainTextEdit->appendPlainText(readData);
    }
  //  readData.clear();
}


void MainWindow::on_pushButton_clicked(bool checked)
{
     if(checked)
     {
           setupSerialPort();
           setupTimer();
     }
     else
     {
         enableOrDisableSomeButtons(true);
         ui->pushButton_2->setEnabled(false);
         timer->stop();
         serialPort->close();
     }
}

void MainWindow::on_pushButton_2_clicked()
{
    QString sendDataStr = ui->textEdit->toPlainText();
    qDebug()<<"str"<<sendDataStr.length();

    QByteArray byteArr;
    byteArr.append(sendDataStr);
    serialPort->write(byteArr.toHex());
    qDebug()<<"send data: "<<byteArr;
    ui->textEdit->append(" 转化为十六进制之后为：" +byteArr.toHex());
    byteArr.capacity();
    byteArr.clear();
}

void MainWindow::on_pushButton_3_clicked()
{
    ui->textEdit->clear();
}

void MainWindow::on_pushButton_4_clicked()
{
    ui->plainTextEdit->clear();
}
