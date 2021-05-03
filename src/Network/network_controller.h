#pragma once

#include <QObject>
#include <QTcpSocket>
#include <QDataStream>

#include "network_data.h"
#include "network_player.h"

class NetworkController : public QObject {
  Q_OBJECT
 public:
  explicit NetworkController(QTcpSocket* socket);
  void SendReadyStatus();
  QVariant GetData();

  signals:
  void StartGame();
  void GotPlayersVector();

 private:
  void ParseData();
  QTcpSocket* socket_;
  QVariant q_variant_;
};



