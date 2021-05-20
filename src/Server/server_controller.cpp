#include "server_controller.h"
#include <iostream>

ServerController::ServerController() :
    ip_(this),
    server_(this) {
  server_.listen(QHostAddress::Any, network::kPort);
  resize(300, 100);
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
          players_cars_data_[player.GetId()] =
              JsonHelper::DecodePlayerCarData(data.data.toString());
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
  network::WriteDataForAll(
      &players_,
      QVariant::fromValue(JsonHelper::EncodePlayersVectorJson(players_)),
      MessageType::kPlayersVector);
}

void ServerController::SendStartSignal(const QVariant& q_variant) {
  network::WriteDataForAll(&players_,
                           q_variant,
                           MessageType::kSignalToStart);
  if(timer_id == -1) {
    timer_id = startTimer(network::kMillisDataSend);
  }
  players_cars_data_.clear();
  players_cars_data_.resize(players_.size());
}

void ServerController::timerEvent(QTimerEvent*) {
  SendGameStateToAllPlayers();
}

void ServerController::SendGameStateToAllPlayers() {
  QString json = JsonHelper::EncodeServerPlayersData(players_cars_data_);
  network::WriteDataForAll(&players_,
                           QVariant::fromValue(json),
                           MessageType::kPlayersCarData);
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
  if(players_cars_data_.empty()) {
    killTimer(timer_id);
  }
  UpdateClientsInfo();
}

void ServerController::SendBonusData(QVariant q_variant) {
  network::WriteDataForAll(&players_,
                           q_variant,
                           MessageType::kNewBonusData);
}
