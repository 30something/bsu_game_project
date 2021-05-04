#include "network_room.h"

NetworkRoom::NetworkRoom(QWidget* parent) :
    QWidget(parent),
    back_to_main_menu_(new QPushButton("Back to main", this)),
    try_connect_(new QPushButton("Connect", this)),
    ready_(new QPushButton("Ready", this)),
    ip_(new QLineEdit("127.0.0.1", this)),
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
  if (network_player_->Socket()->isOpen()) {
    network_player_->SetIsReady(!network_player_->IsReady());
    network_controller_->SendReadyStatus();
  } else {
    connection_status_->setText("You are not connected!");
  }
}

void NetworkRoom::SetUpAndStartGame() {
  // smth here
  emit StartGame();
}

void NetworkRoom::UpdatePlayersVector() {
  QString json =
      network_controller_->GetData().toString();
  auto data_vector = DecodePlayersVectorJson(json);

  QLayoutItem* item;
  while ((item = players_layout_->takeAt(0)) != nullptr) {
    delete item->widget();
    delete item;
  }

  players_.clear();
  for (const auto& data : data_vector) {
    auto* player = new NetworkPlayer(nullptr);
    player->SetId(data.first);
    player->SetIsReady(data.second);
    players_.emplace_back(new PlayerTile(this, player));
    players_layout_->addWidget(players_.back());
  }
  if (!is_first_packet_received) {
    network_player_->SetId(players_.size() - 1);
    is_first_packet_received = true;
    if (network_player_->GetId() == 0) {
      AddStartButton();
    }
  }
  players_[network_player_->GetId()]->Highlight();
}

std::vector<std::pair<size_t, bool>>
NetworkRoom::DecodePlayersVectorJson(const QString& json) {
  QJsonObject json_object = QJsonDocument::fromJson(json.toUtf8()).object();
  QJsonArray data_array = json_object["data"].toArray();
  std::vector<std::pair<size_t, bool>> result;
  for (const auto& data : data_array) {
    QJsonObject data_obj = data.toObject();
    result.emplace_back(data_obj["id"].toInt(),
                        data_obj["status"].toBool());
  }
  return result;
}

void NetworkRoom::AddStartButton() {
  auto* start_button = new QPushButton("Start Game", this);
  buttons_layout_->addWidget(start_button);
  connect(start_button,
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
  network_controller_->SendStartSignal();
  SetUpAndStartGame();
}
