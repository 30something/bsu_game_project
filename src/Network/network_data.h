#pragma once

#include <QVariant>
#include <QTcpSocket>

#include "src/helpers/vec2f.h"
#include "src/network/network_player.h"

enum class MessageType {
  kPlayersVector,
  kReadyStatus,
  kSignalToStart,
  kPlayersCarData,
  kNewBonusData
};

struct NetworkData {
  QVariant data;
  MessageType type;
};

struct PlayerCarData {
  Vec2f position;
  Vec2f angle;
  double hp;
  bool flag_up;
  bool flag_down;
  bool flag_left;
  bool flag_right;
  bool flag_shoot;
  bool flag_mine;
  bool is_updated;
};

struct network {
  static void WriteData(QTcpSocket* socket,
                 const QVariant& q_variant,
                 MessageType type) {
    socket->write(GetDataStruct(q_variant, type));
  }

  static void WriteDataForAll(std::vector<NetworkPlayer>* players_,
                              const QVariant& q_variant,
                              MessageType type) {
    for (auto& player : *players_) {
      player.Socket()->write(GetDataStruct(q_variant, type));
    }
  }

 private:
  static QByteArray GetDataStruct(const QVariant& q_variant,
                                  const MessageType& type) {
    NetworkData data;
    data.type = type;
    data.data = q_variant;
    QByteArray arr;
    QDataStream data_stream(&arr, QIODevice::WriteOnly);
    data_stream << data.type << data.data;
    return arr;
  }
};