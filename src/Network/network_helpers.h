#pragma once

#include <vector>
#include <utility>

#include <QVariant>
#include <QTcpSocket>
#include <QJsonObject>
#include <QJsonArray>
#include <QJsonDocument>

#include "src/helpers/vec2f.h"
#include "src/Network/network_player.h"

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
    socket->write(GetDataBytes(q_variant, type));
  }

  static void WriteDataForAll(std::vector<NetworkPlayer>* players_,
                              const QVariant& q_variant,
                              MessageType type) {
    for (auto& player : *players_) {
      player.Socket()->write(GetDataBytes(q_variant, type));
    }
  }

  static constexpr int kPort = 5555;
  static constexpr int kMillisDataSend = 20;

 private:
  static QByteArray GetDataBytes(const QVariant& q_variant,
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

struct JsonHelper {
  static QString EncodeGameModeJson(int map_index,
                                    int bots_amount,
                                    int laps_amount,
                                    bool enable_drifting) {
    QJsonObject json_object;
    json_object.insert("map_index",
                       QJsonValue::fromVariant(map_index));
    json_object.insert("bots_amount",
                       QJsonValue::fromVariant(bots_amount));
    json_object.insert("laps_amount",
                       QJsonValue::fromVariant(laps_amount));
    json_object.insert("enable_drifting",
                       QJsonValue::fromVariant(enable_drifting));
    return QJsonDocument(json_object).toJson();
  }

  static std::vector<std::pair<size_t, bool>>
  DecodePlayersVectorJson(const QString& json) {
    QJsonObject json_object = QJsonDocument::fromJson(json.toUtf8()).object();
    QJsonArray data_array = json_object["data"].toArray();
    std::vector<std::pair<size_t, bool>> result;
    for (const auto& data : data_array) {
      QJsonObject data_obj = data.toObject();
      result.emplace_back(data_obj["id"].toInt(),
                          data_obj["status"].toBool());
    }
    return result;
  }

  static std::vector<PlayerCarData>
  DecodePlayersCarData(const QVariant& q_variant) {
    // here we get json and convert it into vector
    QString json = q_variant.toString();
    std::vector<PlayerCarData> players_cars_data;
    QJsonObject json_object = QJsonDocument::fromJson(json.toUtf8()).object();
    QJsonArray data_array = json_object["data"].toArray();
    for (const auto& data : data_array) {
      QJsonObject data_obj = data.toObject();
      PlayerCarData car_data;
      QJsonObject angle_obj = data_obj["angle"].toObject();
      car_data.angle = Vec2f(angle_obj["x"].toDouble(),
                             angle_obj["y"].toDouble());
      QJsonObject position_obj = data_obj["position"].toObject();
      car_data.position = Vec2f(position_obj["x"].toDouble(),
                                position_obj["y"].toDouble());
      car_data.hp = data_obj["hp"].toDouble();
      car_data.flag_up = data_obj["flag_up"].toBool();
      car_data.flag_down = data_obj["flag_down"].toBool();
      car_data.flag_left = data_obj["flag_left"].toBool();
      car_data.flag_right = data_obj["flag_right"].toBool();
      car_data.flag_shoot = data_obj["flag_shoot"].toBool();
      car_data.flag_mine = data_obj["flag_mine"].toBool();
      car_data.is_updated = true;
      players_cars_data.push_back(car_data);
    }
    return players_cars_data;
  }

  static QString EncodePlayerCarData(PlayerCarData data) {
    QJsonObject json_object;
    QJsonObject angle_obj;
    angle_obj.insert("x", QJsonValue::fromVariant(data.angle.GetX()));
    angle_obj.insert("y", QJsonValue::fromVariant(data.angle.GetY()));
    json_object.insert("angle", angle_obj);
    QJsonObject position_obj;
    position_obj.insert("x", QJsonValue::fromVariant(data.position.GetX()));
    position_obj.insert("y", QJsonValue::fromVariant(data.position.GetY()));
    json_object.insert("position", position_obj);
    json_object.insert("hp", QJsonValue::fromVariant(data.hp));
    json_object.insert("flag_up", QJsonValue::fromVariant(data.flag_up));
    json_object.insert("flag_down", QJsonValue::fromVariant(data.flag_down));
    json_object.insert("flag_left", QJsonValue::fromVariant(data.flag_left));
    json_object.insert("flag_right", QJsonValue::fromVariant(data.flag_right));
    json_object.insert("flag_shoot", QJsonValue::fromVariant(data.flag_shoot));
    json_object.insert("flag_mine", QJsonValue::fromVariant(data.flag_mine));
    return QJsonDocument(json_object).toJson();
  }

  static QString EncodeNewBonusData(Vec2f position, int type) {
    QJsonObject json_object;
    json_object.insert("x", QJsonValue::fromVariant(position.GetX()));
    json_object.insert("y", QJsonValue::fromVariant(position.GetY()));
    json_object.insert("type", QJsonValue::fromVariant(type));
    return QJsonDocument(json_object).toJson();
  }

  static QString
  EncodePlayersVectorJson(const std::vector<NetworkPlayer>& players) {
    QJsonObject json_object;
    QJsonArray array;
    for (size_t i = 0; i < players.size(); i++) {
      QJsonObject arr_cell;
      arr_cell.insert("id", QJsonValue::fromVariant(static_cast<int>(i)));
      arr_cell.insert("status", QJsonValue::fromVariant(players[i].IsReady()));
      array.push_back(arr_cell);
    }
    json_object.insert("data", array);
    return QJsonDocument(json_object).toJson();
  }

  static QString
  EncodeServerPlayersData(const std::vector<PlayerCarData>& players_cars_data) {
    QJsonObject json_object;
    QJsonArray array;
    for (const auto& data : players_cars_data) {
      QJsonObject arr_cell;
      QJsonObject angle_obj;
      angle_obj.insert("x", QJsonValue::fromVariant(data.angle.GetX()));
      angle_obj.insert("y", QJsonValue::fromVariant(data.angle.GetY()));
      arr_cell.insert("angle", angle_obj);
      QJsonObject position_obj;
      position_obj.insert("x", QJsonValue::fromVariant(data.position.GetX()));
      position_obj.insert("y", QJsonValue::fromVariant(data.position.GetY()));
      arr_cell.insert("position", position_obj);
      arr_cell.insert("hp", QJsonValue::fromVariant(data.hp));
      arr_cell.insert("flag_up", QJsonValue::fromVariant(data.flag_up));
      arr_cell.insert("flag_down", QJsonValue::fromVariant(data.flag_down));
      arr_cell.insert("flag_left", QJsonValue::fromVariant(data.flag_left));
      arr_cell.insert("flag_right", QJsonValue::fromVariant(data.flag_right));
      arr_cell.insert("flag_shoot", QJsonValue::fromVariant(data.flag_shoot));
      arr_cell.insert("flag_mine", QJsonValue::fromVariant(data.flag_mine));
      array.push_back(arr_cell);
    }
    json_object.insert("data", array);
    return QJsonDocument(json_object).toJson();
  }

  static PlayerCarData
  DecodePlayerCarData(const QString& json) {
    PlayerCarData car_data;
    QJsonObject data_obj = QJsonDocument::fromJson(json.toUtf8()).object();
    QJsonObject angle_obj = data_obj["angle"].toObject();
    car_data.angle = Vec2f(angle_obj["x"].toDouble(),
                           angle_obj["y"].toDouble());
    QJsonObject position_obj = data_obj["position"].toObject();
    car_data.position = Vec2f(position_obj["x"].toDouble(),
                              position_obj["y"].toDouble());
    car_data.hp = data_obj["hp"].toDouble();
    car_data.flag_up = data_obj["flag_up"].toBool();
    car_data.flag_down = data_obj["flag_down"].toBool();
    car_data.flag_left = data_obj["flag_left"].toBool();
    car_data.flag_right = data_obj["flag_right"].toBool();
    car_data.flag_shoot = data_obj["flag_shoot"].toBool();
    car_data.flag_mine = data_obj["flag_mine"].toBool();
    return car_data;
  }
};
