#include "network_controller.h"

NetworkController::NetworkController(QTcpSocket* socket) : socket_(socket) {
  connect(socket_,
          &QTcpSocket::readyRead,
          this,
          &NetworkController::ParseData);
}

void NetworkController::SendReadyStatus() {
  //socket_.send(smth);
}

void NetworkController::ParseData() {
  QByteArray arr = socket_->readAll();
  QDataStream data_stream(&arr, QIODevice::ReadOnly);
  NetworkData data;
  data_stream >> data.type;
  data_stream >> data.data;
  switch(data.type) {
    case MessageType::kPlayersVector : {
      q_variant_ = data.data;
      emit GotPlayersVector();
    }
  }
}

QVariant NetworkController::GetData() {
  return q_variant_;
}
