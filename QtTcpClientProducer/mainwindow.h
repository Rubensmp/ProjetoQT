#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTcpSocket>
#include <QDebug>
#include <list>

using namespace std;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
  Q_OBJECT

public:
  explicit MainWindow(QWidget *parent = 0);
  ~MainWindow();
    void tcpConnect(QString str);
public slots:
  void getIP();
  void disconnect();
  void timerEvent(QTimerEvent *e);
  void start();
  void stop();
private:
  Ui::MainWindow *ui;
  QTcpSocket *socket;
  list<QString> lista;
  int temp;

};

#endif // MAINWINDOW_H
