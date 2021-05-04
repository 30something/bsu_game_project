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

class NetworkRoom : public QWidget {
 Q_OBJECT

 public:
  explicit NetworkRoom(QWidget* parent);
  ~NetworkRoom() override = default;

 signals:
  void StartGame();
  void ReturnToMainMenu();

 private:
  QPushButton* back_to_main_menu_;
  QPushButton* try_connect_;
  QPushButton* ready_;
  QLineEdit* ip_;
  QLineEdit* port_;
  QLineEdit* nickname_;
  QLabel* connection_status_;
  QVBoxLayout* main_layout_;
  QVBoxLayout* connection_layout_;
  QHBoxLayout* buttons_layout_;
  QVBoxLayout* players_layout_;

  bool is_first_packet_received = false;

  NetworkPlayer* network_player_ = nullptr;
  std::vector<PlayerTile*> players_;
  NetworkController* network_controller_ = nullptr;
  void UpdatePlayersVector();
  void SetUpAndStartGame();
  void PrepareForStart();
  void ChangeReadyStatus();
  void ConnectToServer();
  void SetUpLayouts();
  void ConnectEverything() const;
  void AddStartButton();

  static std::vector<std::pair<size_t, bool>>
  DecodePlayersVectorJson(const QString& json);
};



