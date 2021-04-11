#include "end_game_stats.h"
#include "src/helpers/sizes.h"

EndGameStats::EndGameStats(QWidget* parent) :
  QWidget(parent),
  stats_label_(new QLabel("You placed 1st place!", this)),
  layout_(new QVBoxLayout(this)),
  return_to_main_menu_button_(new QPushButton("Return to main menu", this)) {
  layout_->setAlignment(Qt::AlignCenter);
  return_to_main_menu_button_->setMinimumSize(button_sizes::kDefaultButtonSize);
  layout_->addWidget(stats_label_, 1, Qt::AlignCenter);
  layout_->addWidget(return_to_main_menu_button_, 1, Qt::AlignCenter);
  connect(return_to_main_menu_button_,
          &QPushButton::clicked,
          this,
          &EndGameStats::ReturnToMainMenu);
}
