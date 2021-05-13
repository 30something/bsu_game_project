#include "end_game_stats.h"
#include "src/helpers/sizes.h"

EndGameStats::EndGameStats(QWidget* parent) :
    QWidget(parent),
    stats_label_(new QLabel("Statistics", this)),
    layout_(new QVBoxLayout(this)),
    return_to_main_menu_button_(new QPushButton("Return to main menu", this)) {}

void EndGameStats::ShowStats(const CarsData& cars_data) {
  layout_->setAlignment(Qt::AlignCenter);
  return_to_main_menu_button_->setMinimumSize(button_sizes::kDefaultButtonSize);
  layout_->addWidget(stats_label_, 5, Qt::AlignCenter);

  auto* positions_layout = new QVBoxLayout;
  std::vector<CarAchievements> cars_achievements = cars_data.cars_data;
  std::sort(cars_achievements.begin(), cars_achievements.end(),
            [](CarAchievements first, CarAchievements second) {
              return first.finish_position < second.finish_position;
            });
  for (uint32_t i = 0; i < cars_achievements.size(); i++) {
    std::string temp_string = std::to_string(i + 1) + ". ";
    if (cars_achievements[i].is_finished) {
      temp_string += std::to_string(cars_achievements[i].elapsed_millis_time);
    } else {
      temp_string += "Dead";
    }
    positions_layout->addWidget(new QLabel(QString::fromStdString(temp_string)),
                                1,
                                Qt::AlignCenter);
  }
  layout_->addLayout(positions_layout);

  layout_->addWidget(return_to_main_menu_button_, 5, Qt::AlignCenter);
  connect(return_to_main_menu_button_,
          &QPushButton::clicked,
          this,
          &EndGameStats::ReturnToMainMenu);
  show();
}
