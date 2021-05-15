#pragma once

#include <vector>
#include <utility>

#include <QWidget>
#include <QTcpSocket>
#include <QTcpServer>
#include <QJsonObject>
#include <QJsonArray>
#include <QJsonDocument>
#include <QTimerEvent>
#include <QLabel>
#include <QNetworkInterface>

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
  QLabel ip_;
  QTcpServer server_;

  static constexpr size_t kServerTimerInterval = 20;

  void ConnectClient();
  void DisconnectClient();
  void ReceiveClientData();
  void UpdateClientsInfo();
  void SendStartSignal(QVariant data);
  void SendGameStateToAllPlayers();
  void SendBonusData(QVariant data);
  QString EncodePlayersData();
  QString EncodePlayersVectorJson();
  void ShowOurIpAddresses();
  void DecodePlayerCarData(NetworkPlayer* player,
                           const QString& json);
};
