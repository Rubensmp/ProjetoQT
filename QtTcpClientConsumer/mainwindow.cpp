#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDateTime>
#include <QListWidget>
#include <vector>

using namespace std;

MainWindow::MainWindow(QWidget *parent) :
  QMainWindow(parent),
  ui(new Ui::MainWindow){
  ui->setupUi(this);
  socket = new QTcpSocket(this);
  tcpConnect();
}

QString ip;

// Conecta ao servidor.
void MainWindow::tcpConnect(){
    ip = ui->lineEdit_Ip->text();
    socket->connectToHost(ip,1234);
    if(socket->waitForConnected(3000)){
        qDebug()<< "Connected";
    }
    else{
        qDebug() << "Disconnected";
    }
}

//Lista os ips que estao conectados ao servidos.
void MainWindow::listaips(){
    ui->listWidget->clear();
    QString str;
    if(socket->state() == QAbstractSocket::ConnectedState){
        if(socket->isOpen()){
            qDebug() << "reading...";
            socket->write("list");
            socket->waitForBytesWritten();
            socket->waitForReadyRead();
            while(socket->bytesAvailable()){
                str = socket->readLine().replace("\n","").replace("\r","");
                ui->listWidget->addItem(str);
            }
        }
    }
}
//Obtem os dados que foram enviados ao servidor pelo produtor de dados.
void MainWindow::getData(){
    QString str;
    QByteArray array;
    QStringList list;
    QDateTime datetime;
    qDebug() << "to get data...";
    qDebug() << socket->state();
    if(socket->state() == QAbstractSocket::ConnectedState){
        if(socket->isOpen()){
            qDebug() << "reading...";
            str = "get "+ip+"\r\n";
            socket->write(str.toUtf8());
            socket->waitForBytesWritten();
            socket->waitForReadyRead();
            qDebug() << socket->bytesAvailable();
            std::vector<int> data;
            std::vector<int>:: iterator i = data.begin();
            std::vector<int>:: iterator ie = data.end();
            while(socket->bytesAvailable()){
                str = socket->readLine().replace("\n","").replace("\r","");
                list = str.split(" ");
                if(list.size() == 2){
                    datetime.fromString(list.at(0),Qt::ISODate);
                    str = list.at(1);
                    qDebug() << datetime << ": " << str;
                    data.push_back(str.toInt());
                    // ui->widgetPlotter(str);
                }
            }
        }
    }
}

// Disconecta do servidor
void MainWindow::disconnect(){
    socket->disconnectFromHost();
    qDebug() << "Disconnected";
}

MainWindow::~MainWindow(){
  delete socket;
  delete ui;
}
