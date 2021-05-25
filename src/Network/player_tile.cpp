#include "player_tile.h"

PlayerTile::PlayerTile(QWidget* parent, const NetworkPlayer* player) :
    QWidget(parent),
    player_(player),
    nickname_(new QLabel(QString::number(player->GetId()), this)),
    is_ready_(new QLabel(this)),
    main_layout_(new QHBoxLayout(this)) {
  setAutoFillBackground(true);
  setPalette(QPalette(QColor(200, 200, 255)));
  nickname_->setFont(fonts::kDefaultLabelFont);
  nickname_->setStyleSheet("QLabel {"
                           "font: bold 18px; }");
  is_ready_->setFont(fonts::kDefaultLabelFont);
  is_ready_->setStyleSheet("QLabel {"
                           "font: bold 18px; }");
  if (player->IsReady()) {
    is_ready_->setText("Ready");
  } else {
    is_ready_->setText("Not ready");
  }
  main_layout_->addWidget(nickname_);
  main_layout_->addWidget(is_ready_);
}

void PlayerTile::Highlight() {
  setAutoFillBackground(true);
  setPalette(QPalette(QColor(255, 200, 200)));
}

const NetworkPlayer* PlayerTile::GetPlayer() const {
  return player_;
}
