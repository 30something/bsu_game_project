#pragma once

#include <algorithm>
#include <string>
#include <vector>

#include <QLabel>
#include <QPainter>
#include <QVBoxLayout>
#include <QWidget>

#include "src/View/view.h"
#include "src/helpers/game_mode.h"
#include "src/helpers/cars_data.h"
#include "src/helpers/fonts.h"

class ViewInfoUpdater {
 public:
  explicit ViewInfoUpdater(QWidget* parent = nullptr,
                           GameMode* game_mode = nullptr);
  ~ViewInfoUpdater() = default;

  void Repaint(QPainter* painter,
               const CarsData& cars_data,
               const std::vector<QRect>& frames,
               double scale);
  void UpdateStartInfo();
  bool GetStartState() const;

 private:
  void UpdateAllInfoDescription(QPainter* painter,
                                const std::vector<QRect>& frames,
                                double scale);
  void UpdateTopInfo(QPainter* painter,
                     int x_pos,
                     int y_pos,
                     int index);
  void UpdateBottomInfo(QPainter* painter,
                        int x_pos,
                        int y_pos,
                        int index);

  QString GetEditedTimeInfo(int index) const;
  QString GetEditedFinishInfo(int index) const;
  static std::string GetSuffix(int value);

  GameMode* game_mode_ = nullptr;
  QLabel* start_label_ = nullptr;
  QLayout* layout_ = nullptr;

  size_t laps_amount_ = 0;
  size_t players_amount_ = 0;
  size_t seconds_before_start_ = 5;
  size_t network_id_ = 0;
  bool is_game_started_ = false;
  CarsData cars_data_;
};
