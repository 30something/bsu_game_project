#pragma once

#include <QPushButton>
#include <QHBoxLayout>
#include <QStackedWidget>
#include <QComboBox>

#include "map_selector_tile.h"
#include "src/helpers/map_data.h"
#include "src/helpers/game_mode.h"

class GameModeSelector : public QWidget {
  Q_OBJECT

 public:
  explicit GameModeSelector(QWidget* parent, GameMode* game_mode);
  ~GameModeSelector() override = default;

 signals:
  void StartGame();
  void ReturnToMainMenu();

 private:
  void SetUpLayout();
  void ConnectUI();
  void PrepareComboBoxes();

  void SwitchRight();
  void SwitchLeft();
  void ApplySettings();

  QPushButton* start_game_;
  QPushButton* back_to_main_menu_;
  QPushButton* left_;
  QPushButton* right_;
  QHBoxLayout* layout_;
  QStackedWidget* stacked_widget_;
  GameMode* game_mode_ = nullptr;
  QComboBox* number_of_players_ = nullptr;
  QComboBox* number_of_bots_ = nullptr;
  static constexpr size_t kMaxPlayersAmount = 2;
  static constexpr size_t kMaxBotsAmount = 6;
};
