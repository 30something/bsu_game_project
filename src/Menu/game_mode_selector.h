#pragma once

#include <QPushButton>
#include <QHBoxLayout>
#include <QStackedWidget>
#include <QLineEdit>

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
  QPushButton* start_game_;
  QPushButton* back_to_main_menu_;
  QPushButton* left_;
  QPushButton* right_;
  QHBoxLayout* layout_;
  QStackedWidget* stacked_widget_;
  GameMode* game_mode_ = nullptr;
  QLineEdit* number_of_players_ = nullptr;
  QLineEdit* number_of_bots_ = nullptr;
  void SwitchRight();
  void SwitchLeft();
  void ApplySettings();
};
