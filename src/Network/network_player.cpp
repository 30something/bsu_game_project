#include "src/Network/network_player.h"

const QString& NetworkPlayer::GetNickname() const {
  return nickname_;
}

void NetworkPlayer::SetNickname(const QString& nickname) {
  nickname_ = nickname;
}

QTcpSocket* NetworkPlayer::Socket(){
  return &socket_;
}

bool NetworkPlayer::IsReady() const {
  return is_ready_;
}

void NetworkPlayer::SetIsReady(bool is_ready) {
  is_ready_ = is_ready;
}
