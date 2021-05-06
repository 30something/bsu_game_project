#pragma once

#include <vector>

#include <QWidget>
#include <QTcpSocket>
#include <QTcpServer>
#include <QJsonObject>
#include <QJsonArray>
#include <QJsonDocument>
#include <QTimerEvent>

#include "src/Network/network_player.h"
#include "src/Network/network_data.h"

class ServerController : public QWidget {
 Q_OBJECT
 public:
  ServerController();

  void timerEvent(QTimerEvent*) override;

 private:
  std::vector<NetworkPlayer> players_;
  std::vector<PlayerCarData> players_cars_data_;

  QTcpServer server_;
  void ConnectClient();
  void ReceiveClientData();
  void UpdateClientsInfo();
  void SendStartSignal();
  void SendGameStateToAllPlayers();
  QString EncodePlayersData();
  QString EncodePlayersVectorJson();
  void DecodePlayerCarData(NetworkPlayer* player,
                           const QString& json);
  static constexpr size_t kServerTimerInterval = 20;
};
