#include "game_mode_selector.h"

GameModeSelector::GameModeSelector(QWidget* parent, GameMode* game_mode) :
    QWidget(parent),
    start_game_(new QPushButton("Start", this)),
    back_to_main_menu_(new QPushButton("Back", this)),
    left_(new QPushButton("Previous", this)),
    right_(new QPushButton("Next", this)),
    layout_(new QHBoxLayout(this)),
    stacked_widget_(new QStackedWidget(this)),
    game_mode_(game_mode),
    number_of_players_(new QLineEdit("players", this)),
    number_of_bots_(new QLineEdit("bots", this)) {
  for (const auto& i : map_data::map_filepaths) {
    stacked_widget_->addWidget(new MapSelectorTile(this, i.second));
  }
  SetUpLayout();
  stacked_widget_->setCurrentIndex(0);
  ConnectUI();
}

void GameModeSelector::SwitchRight() {
  if (game_mode_->map_index >= map_data::map_filepaths.size() - 1) {
    game_mode_->map_index = 0;
  } else {
    game_mode_->map_index++;
  }
  stacked_widget_->setCurrentIndex(game_mode_->map_index);
  repaint();
}

void GameModeSelector::SwitchLeft() {
  if (game_mode_->map_index <= 0) {
    game_mode_->map_index = map_data::map_filepaths.size() - 1;
  } else {
    game_mode_->map_index--;
  }
  stacked_widget_->setCurrentIndex(game_mode_->map_index);
  repaint();
}

void GameModeSelector::ApplySettings() {
  game_mode_->players_amount = number_of_players_->text().toInt();
  game_mode_->bots_amount = number_of_bots_->text().toInt();
  emit StartGame();
}

void GameModeSelector::SetUpLayout() {
  layout_->addWidget(back_to_main_menu_);
  layout_->addWidget(left_);
  layout_->addWidget(stacked_widget_, 0, Qt::AlignCenter);
  layout_->addWidget(right_);
  layout_->addWidget(number_of_players_);
  layout_->addWidget(number_of_bots_);
  layout_->addWidget(start_game_);
}

void GameModeSelector::ConnectUI() {
  connect(left_,
          &QPushButton::clicked,
          this,
          &GameModeSelector::SwitchLeft);
  connect(right_,
          &QPushButton::clicked,
          this,
          &GameModeSelector::SwitchRight);
  connect(start_game_,
          &QPushButton::clicked,
          this,
          &GameModeSelector::ApplySettings);
  connect(back_to_main_menu_,
          &QPushButton::clicked,
          this,
          &GameModeSelector::ReturnToMainMenu);
}
