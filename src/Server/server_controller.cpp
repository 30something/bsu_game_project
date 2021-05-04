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
    QString json_to_send = EncodePlayersVectorJson();
    data.data = QVariant::fromValue(json_to_send);
    QByteArray arr;
    QDataStream data_stream(&arr, QIODevice::WriteOnly);
    data_stream << data.type << data.data;
    player.Socket()->write(arr);
  }
}

QString ServerController::EncodePlayersVectorJson() {
  QJsonObject json_object;
  //array of ids and status ready
  QJsonArray array;
  for(const auto& player : players_) {
    QJsonObject array_cell;
    array_cell.insert("id", QJsonValue::fromVariant(player.GetId()));
    array_cell.insert("status", QJsonValue::fromVariant(player.IsReady()));
    array.push_back(array_cell);
  }
  json_object.insert("data", array);
  return QJsonDocument(json_object).toJson();
}
