#pragma once

#include <utility>
#include <vector>

#include <QWidget>
#include <QPushButton>
#include <QLabel>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QLineEdit>
#include <QJsonObject>
#include <QJsonArray>
#include <QJsonDocument>

#include "network_player.h"
#include "network_controller.h"
#include "player_tile.h"
#include "src/helpers/game_mode.h"
#include "src/helpers/fonts.h"
#include "src/helpers/sizes.h"

class NetworkRoom : public QWidget {
  Q_OBJECT

 public:
  explicit NetworkRoom(QWidget* parent, GameMode* game_mode);
  ~NetworkRoom() override = default;
  void Disconnect();

 signals:
  void StartGame();
  void ReturnToMainMenu();
  void OpenGameModeSelector();
  void ExitDisconnected();

 private:
  void UpdatePlayersVector();
  void SetUpAndStartGame();
  void PrepareForStart();
  void ChangeReadyStatus();
  void Connect();
  void SetUpLayouts();
  void SetStyles();
  void ConnectButtons() const;
  void AddStartButton();
  void DecodeGameModeData();

  QPushButton* back_to_main_menu_;
  QPushButton* try_connect_;
  QPushButton* ready_;
  QPushButton* disconnect_;
  QPushButton* start_button_ = nullptr;
  QLineEdit* ip_;
  QLabel* connection_status_;
  QVBoxLayout* main_layout_;
  QVBoxLayout* connection_layout_;
  QHBoxLayout* buttons_layout_;
  QVBoxLayout* players_layout_;

  bool is_first_packet_received_ = false;
  GameMode* game_mode_ = nullptr;
  NetworkPlayer* network_player_ = nullptr;
  std::vector<PlayerTile*> players_;
  NetworkController* network_controller_ = nullptr;

  static constexpr int kMillisWaitForConnection = 100;
};
