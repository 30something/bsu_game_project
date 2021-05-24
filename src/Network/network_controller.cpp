#include "network_controller.h"

NetworkController::NetworkController(NetworkPlayer* player) : player_(player) {
  connect(player_->Socket(),
          &QTcpSocket::readyRead,
          this,
          &NetworkController::ParseData);
}

void NetworkController::SendReadyStatus() {
  network::WriteData(player_->Socket(),
                     QVariant::fromValue(player_->GetId()),
                     MessageType::kReadyStatus);
}

void NetworkController::ParseData() {
  QByteArray arr = player_->Socket()->readAll();
  QDataStream data_stream(&arr, QIODevice::ReadOnly);
  NetworkData data;
  data_stream >> data.type;
  data_stream >> data.data;
  switch (data.type) {
    case MessageType::kPlayersVector : {
      q_variant_ = data.data;
      emit GotPlayersVector();
      break;
    }
    case MessageType::kSignalToStart : {
      q_variant_ = data.data;
      emit GotSignalToStart();
      break;
    }
    case MessageType::kPlayersCarData : {
      DecodePlayersCarData(data.data);
      break;
    }
    case MessageType::kNewBonusData : {
      q_variant_ = data.data;
      emit GotNewBonusData();
      break;
    }
    case MessageType::kReadyStatus : {
      break;
    }
  }
}

void NetworkController::DecodePlayersCarData(const QVariant& q_variant) {
  // here we get json and convert it into vector
  QString json = q_variant.toString();
  players_cars_data_.clear();
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
    players_cars_data_.push_back(car_data);
  }
}

QVariant NetworkController::GetData() {
  return q_variant_;
}

void NetworkController::SendStartSignal(const QString& json) {
  network::WriteData(player_->Socket(),
                     QVariant::fromValue(json),
                     MessageType::kSignalToStart);
}

bool NetworkController::DataUpdated(size_t id) {
  if (players_cars_data_[id].is_updated) {
    players_cars_data_[id].is_updated = false;
    return true;
  } else {
    return false;
  }
}

PlayerCarData NetworkController::GetPlayersData(size_t id) {
  return players_cars_data_[id];
}

void NetworkController::SendCarData(PlayerCarData data) {
  network::WriteData(player_->Socket(),
                     QVariant::fromValue(JsonHelper::EncodePlayerCarData(data)),
                     MessageType::kPlayersCarData);
}

size_t NetworkController::GetId() {
  return player_->GetId();
}

bool NetworkController::IsAlreadyStarted() const {
  return already_started_;
}

void NetworkController::SetAlreadyStarted(bool already_started) {
  already_started_ = already_started;
}

void NetworkController::SendNewBonusData(Vec2f position, int type) {
  network::WriteData(
      player_->Socket(),
      QVariant::fromValue(JsonHelper::EncodeNewBonusData(position, type)),
      MessageType::kNewBonusData);
}
