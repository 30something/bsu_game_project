#pragma once

#include <QObject>
#include <QTcpSocket>
#include <QDataStream>
#include <QJsonObject>
#include <QJsonArray>
#include <QJsonDocument>

#include "network_data.h"
#include "network_player.h"

class NetworkController : public QObject {
  Q_OBJECT
 public:
  explicit NetworkController(NetworkPlayer* player);
  void SendReadyStatus();
  QVariant GetData();
  void SendStartSignal(const QString& json);
  bool DataUpdated(size_t id);
  PlayerCarData GetPlayersData(size_t id);
  void SendCarData(PlayerCarData player_car_data);
  size_t GetId();

 signals:
  void StartGame();
  void GotPlayersVector();
  void GotSignalToStart();

 private:
  void ParseData();
  void DecodePlayersCarData(const QVariant& q_variant);
  static QString EncodePlayerCarData(PlayerCarData data);
  NetworkPlayer* player_;
  QVariant q_variant_;
  std::vector<PlayerCarData> players_cars_data_;
};
