#pragma once

#include <QWidget>
#include <QTcpSocket>
#include <QTcpServer>
#include <QJsonObject>
#include <QJsonArray>
#include <QJsonDocument>

#include "src/Network/network_player.h"
#include "src/Network/network_data.h"

enum class GameState {
  kLobby,
  kRace
};

class ServerController : public QWidget {
  Q_OBJECT
 public:
  ServerController();

 private:
  std::vector<NetworkPlayer> players_;
  QTcpServer server_;
  GameState game_state = GameState::kLobby;
  void ConnectClient();
  void ReceiveClientData();
  void UpdateClientsInfo();

  QString EncodePlayersVectorJson();
};



