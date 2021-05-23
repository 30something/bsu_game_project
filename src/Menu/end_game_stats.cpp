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
  return_to_main_menu_button_->setStyleSheet(styles::kStandardPushbuttonStyle);
  setStyleSheet("QLabel {"
                "font: bold 26px; }");
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
    std::string image_path = ":resources/images/cars/cars_icons/car";
    image_path += std::to_string(cars_data_.GetNumber(i) + 1) + ".png";
    QString image_path_qt = QString::fromStdString(image_path);
    if (positions_layout_->count() > i) {
      images_[i]->LoadImage(image_path_qt);
      times_[i]->setText(QString::fromStdString(stats_string));
    } else {
      CreateLayouts(i, image_path_qt, stats_string);
    }
  }
  show();
}

void EndGameStats::CreateLayouts(int index,
                                 const QString& image_path,
                                 const std::string& stats_string) {
  auto stats_layout = new QHBoxLayout;
  auto pos_label = new QLabel(QString::fromStdString(
      std::to_string(index + 1) + ") "));
  auto image = new ImageSelectorTile(this, image_path);
  auto time_label = new QLabel(QString::fromStdString(stats_string));
  pos_label->setFont(fonts::kDefaultLabelFont);
  time_label->setFont(fonts::kDefaultLabelFont);
  stats_layout->addStretch(15);
  stats_layout->addWidget(pos_label, 1, Qt::AlignCenter);
  stats_layout->addWidget(image, 1, Qt::AlignCenter);
  stats_layout->addWidget(time_label, 1, Qt::AlignCenter);
  stats_layout->addStretch(15);
  positions_layout_->addLayout(stats_layout);
  images_.emplace_back(image);
  times_.emplace_back(time_label);
}

std::string EndGameStats::CreateStatsString(int index) {
  std::string temp_string = "- ";
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
