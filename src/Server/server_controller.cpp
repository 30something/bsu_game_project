#include "server_controller.h"

ServerController::ServerController() :
    server_(this) {
  server_.listen(QHostAddress::Any, 5555);
  connect(&server_,
          &QTcpServer::newConnection,
          this,
          &ServerController::ConnectClient);
}

void ServerController::ConnectClient() {
  qDebug() << "somebody connected";
  players_.emplace_back(server_.nextPendingConnection());
  players_.back().SetId(players_.size() - 1);
  connect(players_.back().Socket(),
          &QTcpSocket::readyRead,
          this,
          &ServerController::ReceiveClientData);
  UpdateClientsInfo();
}

void ServerController::ReceiveClientData() {
  //switch()
}

void ServerController::UpdateClientsInfo() {
  for(auto& player : players_) {
    NetworkData data;
    data.type = MessageType::kPlayersVector;
    data.data = QVariant::fromValue(players_.back().GetId());
    QByteArray arr;
    QDataStream data_stream(&arr, QIODevice::WriteOnly);
    data_stream << data.type << data.data;
    player.Socket()->write(arr);
  }
}
