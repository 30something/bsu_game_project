#pragma once

#include <QComboBox>
#include <QHBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QStackedWidget>
#include <QCheckBox>

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
  void resizeEvent(QResizeEvent*) override;

  void SetSizes();
  void SetUpLayouts();
  void ConnectUI();
  void PrepareComboBoxes();

  void SwitchRight();
  void SwitchLeft();
  void ApplySettings();

  QPushButton* start_game_;
  QPushButton* back_to_main_menu_;
  QPushButton* left_;
  QPushButton* right_;
  QVBoxLayout* main_layout_;
  QHBoxLayout* picture_layout_;
  QLabel* players_label_;
  QLabel* laps_label_;
  QLabel* bots_label_;
  QCheckBox* enable_drifts_;
  QHBoxLayout* players_layout_;
  QHBoxLayout* laps_layout_;
  QHBoxLayout* bots_layout_;
  QVBoxLayout* boxes_layout_;
  QHBoxLayout* buttons_layout_;
  QStackedWidget* stacked_widget_;
  GameMode* game_mode_ = nullptr;
  QComboBox* number_of_players_ = nullptr;
  QComboBox* number_of_laps_ = nullptr;
  QComboBox* number_of_bots_ = nullptr;

  static constexpr uint32_t kMaxPlayersAmount = 2;
  static constexpr uint32_t kMaxLapsAmount = 10;
  static constexpr uint32_t kMaxBotsAmount = 6;

  static constexpr int32_t kMinimapStartXDivisionCoef = 3;
  static constexpr int32_t kMinimapStartYDivisionCoef = 30;
  static constexpr int32_t kMinimapWidthDivisionCoef = 3;
  static constexpr int32_t kMinimapHeightDivisionCoef = 2;
};
