#include "network_room.h"

NetworkRoom::NetworkRoom(QWidget* parent, GameMode* game_mode) :
    QWidget(parent),
    back_to_main_menu_(new QPushButton("Back to main", this)),
    try_connect_(new QPushButton("Connect", this)),
    ready_(new QPushButton("Ready", this)),
    disconnect_(new QPushButton("Disconnect", this)),
    ip_(new QLineEdit("127.0.0.1", this)),
    connection_status_(new QLabel("Not connected", this)),
    main_layout_(new QVBoxLayout(this)),
    connection_layout_(new QVBoxLayout()),
    buttons_layout_(new QHBoxLayout()),
    players_layout_(new QVBoxLayout()),
    game_mode_(game_mode),
    network_player_(new NetworkPlayer(new QTcpSocket())) {
  SetStyles();
  SetUpLayouts();
  ConnectButtons();
}

void NetworkRoom::ConnectButtons() const {
  connect(back_to_main_menu_,
          &QPushButton::clicked,
          this,
          &NetworkRoom::ReturnToMainMenu);
  connect(try_connect_,
          &QPushButton::clicked,
          this,
          &NetworkRoom::Connect);
  connect(ready_,
          &QPushButton::clicked,
          this,
          &NetworkRoom::ChangeReadyStatus);
  connect(disconnect_,
          &QPushButton::clicked,
          this,
          &NetworkRoom::Disconnect);
}

void NetworkRoom::SetUpLayouts() {
  main_layout_->addLayout(buttons_layout_);
  main_layout_->addLayout(connection_layout_);
  main_layout_->addLayout(players_layout_);
  connection_status_->setAlignment(Qt::AlignCenter);
  connection_layout_->addWidget(ip_);
  connection_layout_->addWidget(connection_status_);
  connection_layout_->addWidget(disconnect_);
  connection_layout_->addWidget(try_connect_);
  buttons_layout_->addWidget(back_to_main_menu_);
  buttons_layout_->addWidget(ready_);
}

void NetworkRoom::SetStyles() {
  for (auto& widget : children()) {
    auto* label_ptr = qobject_cast<QLabel*>(widget);
    auto* button_ptr = qobject_cast<QPushButton*>(widget);
    if (label_ptr) {
      label_ptr->setFont(fonts::kDefaultLabelFont);
      label_ptr->setStyleSheet("QLabel {"
                               "font: bold 18px; }");
    } else if (button_ptr) {
      button_ptr->setFont(fonts::kDefaultButtonFont);
      button_ptr->setMinimumSize(button_sizes::kMultiplayerButtonMinSize);
      button_ptr->setStyleSheet(styles::kStandardPushbuttonStyle);
    }
  }
  ip_->setStyleSheet(styles::kStandardLineEditStyle);
}

void NetworkRoom::Connect() {
  if (network_player_->Socket()->state() == QAbstractSocket::ConnectedState) {
    connection_status_->setText("Already connected");
    return;
  }
  network_player_->Socket()->connectToHost(ip_->text(), network::kPort);
  network_player_->Socket()->waitForConnected(kMillisWaitForConnection);
  if (network_player_->Socket()->state() != QAbstractSocket::ConnectedState) {
    connection_status_->setText("Connection Error");
    return;
  }
  connection_status_->setText("Connected Successfully");
  network_controller_ = new NetworkController(network_player_);
  connect(network_controller_,
          &NetworkController::StartGame,
          this,
          &NetworkRoom::SetUpAndStartGame);
  connect(network_controller_,
          &NetworkController::GotPlayersVector,
          this,
          &NetworkRoom::UpdatePlayersVector);
  connect(network_controller_,
          &NetworkController::GotSignalToStart,
          this,
          &NetworkRoom::SetUpAndStartGame);
}

void NetworkRoom::ChangeReadyStatus() {
  if (network_player_->Socket()->state() == QAbstractSocket::ConnectedState) {
    network_player_->SetIsReady(!network_player_->IsReady());
    network_controller_->SendReadyStatus();
  } else {
    connection_status_->setText("You are not connected!");
  }
}

void NetworkRoom::SetUpAndStartGame() {
  if (!network_controller_->IsAlreadyStarted()) {
    if (network_controller_->GetId() != 0) {
      DecodeGameModeData();
    }
    game_mode_->network_players_amount = players_.size() - 1;
    game_mode_->network_controller = network_controller_;
    if (network_player_->GetId() == 0) {
      emit OpenGameModeSelector();
    } else {
      emit StartGame();
    }
  }
}

void NetworkRoom::UpdatePlayersVector() {
  QString json = network_controller_->GetData().toString();
  auto data_vector = JsonHelper::DecodePlayersVectorJson(json);

  QLayoutItem* item;
  while ((item = players_layout_->takeAt(0)) != nullptr) {
    delete item->widget();
    delete item;
  }
  if (data_vector.size() < players_.size()) {
    Disconnect();
    return;
  }
  players_.clear();
  for (const auto& data : data_vector) {
    auto* player = new NetworkPlayer(nullptr);
    player->SetId(data.first);
    player->SetIsReady(data.second);
    players_.emplace_back(new PlayerTile(this, player));
    players_layout_->addWidget(players_.back());
  }
  if (!is_first_packet_received_) {
    network_player_->SetId(players_.size() - 1);
    is_first_packet_received_ = true;
    if (network_player_->GetId() == 0) {
      AddStartButton();
    }
  }
  players_[network_player_->GetId()]->Highlight();
}

void NetworkRoom::AddStartButton() {
  start_button_ = new QPushButton("Start Game", this);
  start_button_->setFont(fonts::kDefaultButtonFont);
  start_button_->setMinimumSize(button_sizes::kMultiplayerButtonMinSize);
  start_button_->setStyleSheet(styles::kStandardPushbuttonStyle);
  buttons_layout_->addWidget(start_button_);
  connect(start_button_,
          &QPushButton::clicked,
          this,
          &NetworkRoom::PrepareForStart);
}

void NetworkRoom::PrepareForStart() {
  for (const auto& player : players_) {
    if (!player->GetPlayer()->IsReady()) {
      connection_status_->setText("Error! Not everybody is ready");
      return;
    }
  }
  SetUpAndStartGame();
}

void NetworkRoom::DecodeGameModeData() {
  QString json = network_controller_->GetData().toString();
  QJsonObject json_object = QJsonDocument::fromJson(json.toUtf8()).object();
  game_mode_->map_index = json_object["map_index"].toInt();
  game_mode_->bots_amount = json_object["bots_amount"].toInt();
  game_mode_->enable_drifting = json_object["enable_drifting"].toBool();
  game_mode_->laps_amount = json_object["laps_amount"].toInt();
}

void NetworkRoom::Disconnect() {
  if (network_player_->Socket()->state() != QAbstractSocket::ConnectedState) {
    connection_status_->setText("You are not connected to disconnect!");
    return;
  }
  if (network_controller_->IsAlreadyStarted()) {
    emit ExitDisconnected();
  }
  network_player_->Socket()->disconnectFromHost();
  QLayoutItem* item;
  while ((item = players_layout_->takeAt(0)) != nullptr) {
    delete item->widget();
    delete item;
  }
  connection_status_->setText("Disconnected from the server");
  buttons_layout_->removeWidget(start_button_);
  delete start_button_;
  start_button_ = nullptr;
  players_.clear();
  network_player_->SetIsReady(false);
  delete network_controller_;
  network_controller_ = nullptr;
  is_first_packet_received_ = false;
}
