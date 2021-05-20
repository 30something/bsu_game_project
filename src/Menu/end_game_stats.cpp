#include "end_game_stats.h"

EndGameStats::EndGameStats(QWidget* parent) :
    QWidget(parent),
    stats_label_(new QLabel("Statistics", this)),
    layout_(new QVBoxLayout(this)),
    positions_layout_(new QVBoxLayout),
    return_to_main_menu_button_(new QPushButton("Return to main menu", this)) {
  SetInfo();
}

void EndGameStats::SetInfo() {
  stats_label_->setFont(fonts::kDefaultStatsFont);
  return_to_main_menu_button_->setMinimumSize(button_sizes::kDefaultButtonSize);
  return_to_main_menu_button_->setFont(fonts::kDefaultButtonFont);
  layout_->setAlignment(Qt::AlignCenter);
  layout_->addWidget(stats_label_, 5, Qt::AlignCenter);
  layout_->addLayout(positions_layout_);
  layout_->addWidget(return_to_main_menu_button_, 5, Qt::AlignCenter);
  connect(return_to_main_menu_button_,
          &QPushButton::clicked,
          this,
          &EndGameStats::ReturnToMainMenu);
  connect(&finish_info_update_timer_,
          &QTimer::timeout,
          this,
          &EndGameStats::UpdateStats);
}

void EndGameStats::LaunchFinishStats() {
  finish_info_update_timer_.start(kMillisPerFinishInfoUpdate);
}

void EndGameStats::UpdateData(const CarsData& cars_data) {
  cars_data_ = cars_data;
}

void EndGameStats::UpdateStats() {
  emit DataRequest();
  std::sort(cars_data_.cars_data.begin(), cars_data_.cars_data.end(),
            [](CarAchievements first, CarAchievements second) {
              return !second.finish_position || (first.finish_position > 0 &&
                  first.finish_position < second.finish_position);
            });
  for (int i = 0; i < static_cast<int>(cars_data_.cars_data.size()); i++) {
    std::string stats_string = CreateStatsString(i);
    if (positions_layout_->count() > i) {
      qobject_cast<QLabel*>(positions_layout_->itemAt(i)->widget())->setText(
          QString::fromStdString(stats_string));
    } else {
      positions_layout_->addWidget(
          new QLabel(QString::fromStdString(stats_string)), 1, Qt::AlignCenter);
      qobject_cast<QLabel*>(positions_layout_->itemAt(i)->widget())->setFont(
          fonts::kDefaultStatsFont);
    }
  }
  show();
}

std::string EndGameStats::CreateStatsString(int index) {
  auto temp_string = std::to_string(index + 1) + ") ";
  temp_string += std::to_string(
      cars_data_.cars_data[index].car_number + 1) + " - ";
  if (cars_data_.cars_data[index].is_finished) {
    std::vector<size_t> parsed_time = physics::TimeParse(
        cars_data_.cars_data[index].elapsed_millis_time);
    size_t minutes = parsed_time[0];
    size_t seconds = parsed_time[1];
    size_t millis = parsed_time[2];
    if (minutes > 0) {
      temp_string += std::to_string(minutes) + " min ";
    }
    temp_string += std::to_string(seconds) + " sec " +
        std::to_string(millis) + " ms";
  } else if (cars_data_.cars_data[index].hit_points_ <= 0) {
    temp_string += "Dead";
  } else {
    temp_string += "Not finished";
  }
  return temp_string;
}
