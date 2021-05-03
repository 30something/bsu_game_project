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
  //socket.readall()
  // switch...
  // emit...
}
