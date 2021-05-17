#include "end_game_stats.h"
#include "src/helpers/sizes.h"
#include <iostream>

EndGameStats::EndGameStats(QWidget* parent) :
    QWidget(parent),
    stats_label_(new QLabel("Statistics", this)),
    layout_(new QVBoxLayout(this)),
    positions_layout_(new QVBoxLayout),
    return_to_main_menu_button_(new QPushButton("Return to main menu", this)) {
  layout_->setAlignment(Qt::AlignCenter);
  return_to_main_menu_button_->setMinimumSize(button_sizes::kDefaultButtonSize);
  layout_->addWidget(stats_label_, 5, Qt::AlignCenter);
  layout_->addLayout(positions_layout_);
  layout_->addWidget(return_to_main_menu_button_, 5, Qt::AlignCenter);
  connect(return_to_main_menu_button_,
          &QPushButton::clicked,
          this,
          &EndGameStats::ReturnToMainMenu);
}

void EndGameStats::UpdateStats(const CarsData& cars_data) {
  std::vector<CarAchievements> cars_achievements = cars_data.cars_data;
  std::sort(cars_achievements.begin(), cars_achievements.end(),
            [](CarAchievements first, CarAchievements second) {
              return first.finish_position < second.finish_position;
            });
  for (int i = 0; i < static_cast<int>(cars_achievements.size()); i++) {
    std::string temp_string = std::to_string(i + 1) + ") ";
    temp_string += std::to_string(cars_achievements[i].car_number + 1) + " - ";
    if (cars_achievements[i].is_finished) {
      size_t overall_millis = cars_achievements[i].elapsed_millis_time;
      size_t minutes = overall_millis / 60000;
      size_t seconds = (overall_millis % 60000) / 1000;
      size_t millis = overall_millis % 1000;
      temp_string += std::to_string(minutes) + " min " +
          std::to_string(seconds) + " sec " +
          std::to_string(millis) + " ms";
    } else if (cars_achievements[i].hit_points_ <= 0) {
      temp_string += "Dead";
    } else {
      temp_string += "Not finished";
    }
    if (positions_layout_->count() > i) {
      qobject_cast<QLabel*>(positions_layout_->itemAt(i)->widget())->setText(
          QString::fromStdString(temp_string));
    } else {
      positions_layout_->addWidget(
          new QLabel(QString::fromStdString(temp_string)), 1, Qt::AlignCenter);
    }
  }
  show();
}
