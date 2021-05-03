#pragma once

#include <QObject>
#include <QTcpSocket>

class NetworkController : public QObject {
  Q_OBJECT
 public:
  explicit NetworkController(QTcpSocket* socket);
  void SendReadyStatus();

  signals:
  void StartGame();

 private:
  void ParseData();
  QTcpSocket* socket_;
};



