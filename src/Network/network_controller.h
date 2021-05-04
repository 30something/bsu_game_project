#pragma once

#include <QObject>
#include <QTcpSocket>
#include <QDataStream>

#include "network_data.h"
#include "network_player.h"

class NetworkController : public QObject {
  Q_OBJECT
 public:
  explicit NetworkController(NetworkPlayer* player);
  void SendReadyStatus();
  QVariant GetData();
  void SendStartSignal();

  signals:
  void StartGame();
  void GotPlayersVector();
  void GotSignalToStart();

 private:
  void ParseData();
  NetworkPlayer* player_;
  QVariant q_variant_;
};



