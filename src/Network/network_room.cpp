#include "network_room.h"

NetworkRoom::NetworkRoom(QWidget* parent) :
    QWidget(parent),
    back_to_main_menu_(new QPushButton("Back to main", this)),
    try_connect_(new QPushButton("Connect", this)),
    ready_(new QPushButton("Ready", this)),
    ip_(new QLineEdit("ip", this)),
    port_(new QLineEdit("5555", this)),
    nickname_(new QLineEdit("unnamed_player", this)),
    connection_status_(new QLabel("Not connected", this)),
    main_layout_(new QVBoxLayout(this)),
    connection_layout_(new QVBoxLayout()),
    buttons_layout_(new QHBoxLayout()),
    players_layout_(new QVBoxLayout()),
    network_player_(new NetworkPlayer()),
    player_tile_(new PlayerTile(this, network_player_)) {
  SetUpLayouts();
  ConnectEverything();
}

void NetworkRoom::ConnectEverything() const {
  connect(back_to_main_menu_,
          &QPushButton::clicked,
          this,
          &NetworkRoom::ReturnToMainMenu);
}

void NetworkRoom::SetUpLayouts() {
  main_layout_->addLayout(buttons_layout_);
  main_layout_->addLayout(connection_layout_);
  main_layout_->addLayout(players_layout_);
  players_layout_->addWidget(player_tile_);
  connection_layout_->addWidget(ip_);
  connection_layout_->addWidget(port_);
  connection_layout_->addWidget(nickname_);
  connection_layout_->addWidget(connection_status_);
  connection_layout_->addWidget(try_connect_);
  buttons_layout_->addWidget(back_to_main_menu_);
  buttons_layout_->addWidget(ready_);
}
