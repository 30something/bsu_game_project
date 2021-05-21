#pragma once

#include <vector>

#include <QObject>
#include <QTcpSocket>
#include <QDataStream>
#include <QJsonObject>
#include <QJsonArray>
#include <QJsonDocument>

#include "network_helpers.h"
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
  bool IsAlreadyStarted() const;
  void SetAlreadyStarted(bool already_started);
  void SendNewBonusData(Vec2f position, int type);

 signals:
  void StartGame();
  void GotPlayersVector();
  void GotSignalToStart();
  void GotNewBonusData();

 private:
  void DecodePlayersCarData(const QVariant& q_variant);
  void ParseData();
  NetworkPlayer* player_;
  QVariant q_variant_;
  std::vector<PlayerCarData> players_cars_data_;
  bool already_started_ = false;
};
