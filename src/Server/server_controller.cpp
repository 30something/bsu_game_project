#include "server_controller.h"

ServerController::ServerController() :
    ip_(this),
    server_(this) {
  server_.listen(QHostAddress::Any, network::kPort);
  connect(&server_,
          &QTcpServer::newConnection,
          this,
          &ServerController::ConnectClient);
  ShowOurIpAddresses();
}

void ServerController::ShowOurIpAddresses() {
  QString ips;
  QList<QHostAddress> addr = QNetworkInterface::allAddresses();
  for (const auto& address : addr) {
    ips += address.toString();
    ips += '\n';
  }
  ip_.setText(ips);
}

void ServerController::ConnectClient() {
  players_.emplace_back(server_.nextPendingConnection());
  players_.back().SetId(players_.size() - 1);
  connect(players_.back().Socket(),
          &QTcpSocket::readyRead,
          this,
          &ServerController::ReceiveClientData);
  connect(players_.back().Socket(),
          &QTcpSocket::disconnected,
          this,
          &ServerController::DisconnectClient);
  UpdateClientsInfo();
}

void ServerController::ReceiveClientData() {
  for (auto& player : players_) {
    if (player.Socket()->bytesAvailable()) {
      QByteArray arr = player.Socket()->readAll();
      QDataStream data_stream(&arr, QIODevice::ReadOnly);
      NetworkData data;
      data_stream >> data.type;
      data_stream >> data.data;
      switch (data.type) {
        case MessageType::kReadyStatus : {
          size_t id = data.data.toInt();
          players_[id].SetIsReady(!players_[id].IsReady());
          UpdateClientsInfo();
          break;
        }
        case MessageType::kSignalToStart : {
          players_cars_data_.clear();
          SendStartSignal(data.data);
          break;
        }
        case MessageType::kPlayersCarData : {
          DecodePlayerCarData(&player, data.data.toString());
          break;
        }
        case MessageType::kNewBonusData : {
          SendBonusData(data.data);
          break;
        }
      }
    }
  }
}

void ServerController::UpdateClientsInfo() {
  network::WriteDataForAll(&players_,
                           QVariant::fromValue(EncodePlayersVectorJson()),
                           MessageType::kPlayersVector);
}

QString ServerController::EncodePlayersVectorJson() {
  QJsonObject json_object;
  QJsonArray array;
  for (size_t i = 0; i < players_.size(); i++) {
    QJsonObject arr_cell;
    arr_cell.insert("id", QJsonValue::fromVariant(static_cast<int>(i)));
    arr_cell.insert("status", QJsonValue::fromVariant(players_[i].IsReady()));
    array.push_back(arr_cell);
  }
  json_object.insert("data", array);
  return QJsonDocument(json_object).toJson();
}

void ServerController::SendStartSignal(QVariant q_variant) {
  network::WriteDataForAll(&players_,
                           q_variant,
                           MessageType::kSignalToStart);
  startTimer(network::kMillisDataSend);
  players_cars_data_.resize(players_.size());
}

void ServerController::timerEvent(QTimerEvent*) {
  SendGameStateToAllPlayers();
}

void ServerController::SendGameStateToAllPlayers() {
  QString json = EncodePlayersData();
  network::WriteDataForAll(&players_,
                           QVariant::fromValue(EncodePlayersData()),
                           MessageType::kPlayersCarData);
}

QString ServerController::EncodePlayersData() {
  QJsonObject json_object;
  QJsonArray array;
  for (const auto& data : players_cars_data_) {
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

void ServerController::DecodePlayerCarData(NetworkPlayer* player,
                                           const QString& json) {
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
  players_cars_data_[player->GetId()] = car_data;
}

void ServerController::DisconnectClient() {
  for (size_t i = 0; i < players_.size(); i++) {
    if (players_[i].Socket()->state() == QAbstractSocket::UnconnectedState) {
      players_.erase(players_.begin() + i);
      if (!players_cars_data_.empty()) {
        players_cars_data_.erase(players_cars_data_.begin() + i);
      }
    }
  }
  for (size_t i = 0; i < players_.size(); i++) {
    players_[i].SetId(i);
  }
  UpdateClientsInfo();
}

void ServerController::SendBonusData(QVariant q_variant) {
  network::WriteDataForAll(&players_,
                           q_variant,
                           MessageType::kNewBonusData);
}
