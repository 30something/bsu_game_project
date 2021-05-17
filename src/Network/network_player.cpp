#include "src/Network/network_player.h"

size_t NetworkPlayer::GetId() const {
  return id_;
}

void NetworkPlayer::SetId(size_t id) {
  id_ = id;
}

QTcpSocket* NetworkPlayer::Socket() {
  return socket_;
}

bool NetworkPlayer::IsReady() const {
  return is_ready_;
}

void NetworkPlayer::SetIsReady(bool is_ready) {
  is_ready_ = is_ready;
}

NetworkPlayer::NetworkPlayer(QTcpSocket* p_socket) : socket_(p_socket) {
}
