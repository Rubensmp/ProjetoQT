#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDateTime>

MainWindow::MainWindow(QWidget *parent) :
  QMainWindow(parent),
  ui(new Ui::MainWindow){
  ui->setupUi(this);
  socket = new QTcpSocket(this);
}

// Conecta ao servidor
void MainWindow::tcpConnect(QString str){
  socket->connectToHost(str,1234);
  qDebug() << str;
  if(socket->waitForConnected(3000)){
    qDebug() << "Connected";
  }
  else{
    qDebug() << "Disconnected";
  }
}

// Obtem o ip
void MainWindow::getIP(){
    QString str= ui->lineEdit->text();
    tcpConnect(str);
}
// Disconecta do servidor
void MainWindow::disconnect(){
    socket->disconnectFromHost();
    qDebug() << "Disconnected";
}

//Transmitir os dados para o servidor
void MainWindow::timerEvent(QTimerEvent *e){
        QDateTime datetime;
        QString str;
        datetime = QDateTime::currentDateTime();
        str = "set "+
                datetime.toString(Qt::ISODate)+
                " "+
                QString::number(qrand()%int(ui->lcdNumber_Max->value()-ui->lcdNumber_Min->value())+ui->lcdNumber_Min->value());
        lista.push_back(str);
        ui->plainTextEdit->appendPlainText(str);
        qDebug() << socket->write(str.toStdString().c_str()) << " bytes written";

}
//Iniciar a transmissão de dados
void MainWindow::start(){
    int t;
    t = ui->horizontalSlider_Timing->value();
    temp=startTimer(t*1000);

}
//Finalizar a transmissão de dados
void MainWindow::stop(){
        killTimer(temp);
}

//Destrutor
MainWindow::~MainWindow(){
  delete socket;
  delete ui;
}
