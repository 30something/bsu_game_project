#pragma once

#include <vector>

#include <QLabel>
#include <QPainter>
#include <QVBoxLayout>
#include <QWidget>

#include "src/View/view.h"
#include "src/helpers/game_mode.h"
#include "src/helpers/cars_data.h"

class ViewInfoUpdater {
 public:
  explicit ViewInfoUpdater(QWidget* parent = nullptr,
                           View* view = nullptr,
                           GameMode* game_mode = nullptr);
  ~ViewInfoUpdater() = default;

  void Repaint(QPainter* painter,
               const CarsData& cars_data);

  void UpdateStartInfo();
  void UpdateAllInfoDescription(QPainter* painter);
  void UpdatePlayerInfoDescription(QPainter* painter,
                                   int x_pos,
                                   int y_pos,
                                   int index);

  bool GetStartState() const;

 private:
  GameMode* game_mode_ = nullptr;
  View* view_ = nullptr;
  QWidget* parent_ = nullptr;
  QLabel* start_label_ = nullptr;
  QLayout* layout_ = nullptr;

  uint32_t laps_amount_ = 0;
  int seconds_before_start_ = 5;
  bool is_game_started_ = false;
  CarsData cars_data_;

  static constexpr double kScale = 2;
  static constexpr int kDescriptionOffset = 10;
};
