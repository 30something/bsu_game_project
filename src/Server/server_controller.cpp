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
          SendStartSignal();
          break;
        }
      }
    }
  }
}

void ServerController::UpdateClientsInfo() {
  for (auto& player : players_) {
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
  QJsonArray array;
  for (const auto& player : players_) {
    QJsonObject arr_cell;
    arr_cell.insert("id",
                    QJsonValue::fromVariant(static_cast<int>(player.GetId())));
    arr_cell.insert("status",
                    QJsonValue::fromVariant(player.IsReady()));
    array.push_back(arr_cell);
  }
  json_object.insert("data", array);
  return QJsonDocument(json_object).toJson();
}

void ServerController::SendStartSignal() {
  for (auto& player : players_) {
    NetworkData data;
    data.type = MessageType::kSignalToStart;
    data.data = QVariant::fromValue(1);
    QByteArray arr;
    QDataStream data_stream(&arr, QIODevice::WriteOnly);
    data_stream << data.type << data.data;
    player.Socket()->write(arr);
  }
}
