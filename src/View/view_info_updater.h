#pragma once

#include <QLabel>
#include <QPainter>
#include <QVBoxLayout>
#include <QWidget>

#include "src/GameCore/game_controller.h"
#include "src/View/view.h"
#include "src/helpers/game_mode.h"

class ViewInfoUpdater {
 public:
  explicit ViewInfoUpdater(QWidget* parent = nullptr,
                           GameController* game_controller = nullptr,
                           View* view = nullptr,
                           GameMode* game_mode = nullptr);
  ~ViewInfoUpdater() = default;

  void Repaint(QPainter* painter);

  void UpdateStartInfo();
  void UpdateAllInfoDescription(QPainter* painter);
  void UpdatePlayerInfoDescription(QPainter* painter,
                                   int x_pos,
                                   int y_pos,
                                   int index);

  bool GetStartState() const;

 private:
  GameController* game_controller_ = nullptr;
  GameMode* game_mode_ = nullptr;
  View* view_ = nullptr;
  QWidget* parent_ = nullptr;
  QLabel* start_label_ = nullptr;
  QLayout* layout_ = nullptr;

  uint32_t laps_amount_ = 0;
  int seconds_before_start_ = 4;
  bool is_game_started_ = false;

  static constexpr double kScale = 2;
};
