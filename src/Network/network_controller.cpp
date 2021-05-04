#include "network_controller.h"

NetworkController::NetworkController(NetworkPlayer* player) : player_(player) {
  connect(player_->Socket(),
          &QTcpSocket::readyRead,
          this,
          &NetworkController::ParseData);
}

void NetworkController::SendReadyStatus() {
  NetworkData data;
  data.type = MessageType::kReadyStatus;
  data.data = QVariant::fromValue(player_->GetId());
  QByteArray arr;
  QDataStream data_stream(&arr, QIODevice::WriteOnly);
  data_stream << data.type << data.data;
  player_->Socket()->write(arr);
}

void NetworkController::ParseData() {
  QByteArray arr = player_->Socket()->readAll();
  QDataStream data_stream(&arr, QIODevice::ReadOnly);
  NetworkData data;
  data_stream >> data.type;
  data_stream >> data.data;
  switch(data.type) {
    case MessageType::kPlayersVector : {
      q_variant_ = data.data;
      emit GotPlayersVector();
      break;
    }
    case MessageType::kSignalToStart : {
      emit GotSignalToStart();
      break;
    }
  }
}

QVariant NetworkController::GetData() {
  return q_variant_;
}

void NetworkController::SendStartSignal() {
  NetworkData data;
  data.type = MessageType::kSignalToStart;
  data.data = QVariant::fromValue(player_->GetId());
  QByteArray arr;
  QDataStream data_stream(&arr, QIODevice::WriteOnly);
  data_stream << data.type << data.data;
  player_->Socket()->write(arr);
}
