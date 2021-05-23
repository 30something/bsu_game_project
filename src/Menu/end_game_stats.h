#pragma once

#include <algorithm>
#include <string>
#include <vector>

#include <QLabel>
#include <QVBoxLayout>
#include <QPushButton>
#include <QTimer>
#include <QWidget>

#include "src/Menu/image_selector_tile.h"
#include "src/helpers/cars_data.h"
#include "src/helpers/fonts.h"
#include "src/helpers/sizes.h"
#include "src/helpers/physics.h"

class EndGameStats : public QWidget {
  Q_OBJECT

 public:
  explicit EndGameStats(QWidget* parent = nullptr);
  ~EndGameStats() override = default;

  void LaunchFinishStats();
  void UpdateData(const CarsData& cars_data);

 signals:
  void DataRequest();
  void ReturnToMainMenu();

 private:
  void UpdateStats();
  void SetInfo();
  std::string CreateStatsString(int index);

  QLabel* stats_label_ = nullptr;
  QVBoxLayout* layout_ = nullptr;
  QVBoxLayout* positions_layout_ = nullptr;
  QPushButton* return_to_main_menu_button_ = nullptr;
  QTimer finish_info_update_timer_;
  CarsData cars_data_;
  std::vector<ImageSelectorTile*> images_;
  std::vector<QLabel*> times_;

  static constexpr int kMillisPerFinishInfoUpdate = 20;
};
