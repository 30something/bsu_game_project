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
    network_player_(new NetworkPlayer(new QTcpSocket())) {
  SetUpLayouts();
  ConnectEverything();
}

void NetworkRoom::ConnectEverything() const {
  connect(back_to_main_menu_,
          &QPushButton::clicked,
          this,
          &NetworkRoom::ReturnToMainMenu);
  connect(try_connect_,
          &QPushButton::clicked,
          this,
          &NetworkRoom::ConnectToServer);
  connect(ready_,
          &QPushButton::clicked,
          this,
          &NetworkRoom::ChangeReadyStatus);
}

void NetworkRoom::SetUpLayouts() {
  main_layout_->addLayout(buttons_layout_);
  main_layout_->addLayout(connection_layout_);
  main_layout_->addLayout(players_layout_);
  connection_layout_->addWidget(ip_);
  connection_layout_->addWidget(port_);
  connection_layout_->addWidget(nickname_);
  connection_layout_->addWidget(connection_status_);
  connection_layout_->addWidget(try_connect_);
  buttons_layout_->addWidget(back_to_main_menu_);
  buttons_layout_->addWidget(ready_);
}

void NetworkRoom::ConnectToServer() {
  network_player_->Socket()->connectToHost(ip_->text(), port_->text().toInt());
  if (network_player_->Socket()->isOpen()) {
    connection_status_->setText("Connected Successfully");
  } else {
    connection_status_->setText("Connection Error");
  }
  network_controller_ = new NetworkController(network_player_->Socket());
  connect(network_controller_,
          &NetworkController::StartGame,
          this,
          &NetworkRoom::SetUpAndStartGame);
  connect(network_controller_,
          &NetworkController::GotPlayersVector,
          this,
          &NetworkRoom::UpdatePlayersVector);
}

void NetworkRoom::ChangeReadyStatus() {
  if (network_player_->Socket()->isOpen()) {
    network_controller_->SendReadyStatus();
    network_player_->SetIsReady(!network_player_->IsReady());
  } else {
    connection_status_->setText("You are not connected!");
  }
}

void NetworkRoom::SetUpAndStartGame() {
  // smth here
  emit StartGame();
}

void NetworkRoom::UpdatePlayersVector() {
  auto id =
      network_controller_->GetData().toInt();
  auto* player = new NetworkPlayer(nullptr);
  player->SetId(id);
  other_players_.emplace_back(new PlayerTile(this, player));
  players_layout_->addWidget(other_players_.back());
}
