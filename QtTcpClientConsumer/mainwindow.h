#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTcpSocket>
#include <QDebug>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
  Q_OBJECT

public:
  explicit MainWindow(QWidget *parent = 0);
  ~MainWindow();
public slots:
  void tcpConnect();
  void getData();
  void disconnect();
  void listaips();
private:
  Ui::MainWindow *ui;
  QTcpSocket *socket;
  int temp;
};

#endif // MAINWINDOW_H
