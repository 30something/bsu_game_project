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
      players_cars_data_ = JsonHelper::DecodePlayersCarData(data.data);
      break;
    }
    case MessageType::kNewBonusData : {
      q_variant_ = data.data;
      emit GotNewBonusData();
      break;
    }
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
