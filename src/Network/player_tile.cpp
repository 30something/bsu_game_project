#include "player_tile.h"

PlayerTile::PlayerTile(QWidget* parent, const NetworkPlayer* player) :
    QWidget(parent),
    player_(player),
    nickname_(new QLabel(player->GetNickname(), this)),
    is_ready_(new QLabel(this)),
    main_layout_(new QHBoxLayout(this)) {
  if(player->IsReady()) {
    is_ready_->setText("ready");
  } else {
    is_ready_->setText("not ready");
  }
  main_layout_->addWidget(nickname_);
  main_layout_->addWidget(is_ready_);
}

void PlayerTile::UpdateInfo() {
  if(player_->IsReady()) {
    is_ready_->setText("ready");
  } else {
    is_ready_->setText("not ready");
  }
  nickname_->setText(player_->GetNickname());
}
