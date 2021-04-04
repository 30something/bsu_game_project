#include "game_mode_selector.h"

GameModeSelector::GameModeSelector(QWidget* parent, GameMode* game_mode) :
    QWidget(parent),
    start_game_(new QPushButton("Start", this)),
    back_to_main_menu_(new QPushButton("Back", this)),
    left_(new QPushButton("Previous", this)),
    right_(new QPushButton("Next", this)),
    main_layout_(new QVBoxLayout(this)),
    picture_layout_(new QHBoxLayout),
    boxes_layout_(new QHBoxLayout),
    buttons_layout_(new QHBoxLayout),
    stacked_widget_(new QStackedWidget(this)),
    game_mode_(game_mode),
    number_of_players_(new QComboBox(this)),
    number_of_laps_(new QComboBox(this)),
    number_of_bots_(new QComboBox(this)) {
  for (const auto& image : map_data::image_filepaths) {
    stacked_widget_->addWidget(new MapSelectorTile(this, image));
  }
  PrepareComboBoxes();
  SetUpLayouts();
  stacked_widget_->setCurrentIndex(0);
  ConnectUI();
}

void GameModeSelector::PrepareComboBoxes() {
  for (size_t i = 1; i <= kMaxPlayersAmount; i++) {
    number_of_players_->addItem(QString::number(i));
  }
  for (size_t i = 1; i <= kMaxBotsAmount; i++) {
    number_of_bots_->addItem(QString::number(i));
  }
  for (size_t i = 1; i <= kMaxLapsAmount; i++) {
    number_of_laps_->addItem(QString::number(i));
  }
}

void GameModeSelector::SwitchRight() {
  if (game_mode_->map_index >= map_data::image_filepaths.size() - 1) {
    game_mode_->map_index = 0;
  } else {
    game_mode_->map_index++;
  }
  stacked_widget_->setCurrentIndex(game_mode_->map_index);
  repaint();
}

void GameModeSelector::SwitchLeft() {
  if (game_mode_->map_index <= 0) {
    game_mode_->map_index = map_data::image_filepaths.size() - 1;
  } else {
    game_mode_->map_index--;
  }
  stacked_widget_->setCurrentIndex(game_mode_->map_index);
  repaint();
}

void GameModeSelector::ApplySettings() {
  game_mode_->players_amount = number_of_players_->currentIndex() + 1;
  game_mode_->laps_amount = number_of_laps_->currentIndex() + 1;
  game_mode_->bots_amount = number_of_bots_->currentIndex() + 1;
}

void GameModeSelector::SetUpLayouts() {
  main_layout_->addLayout(picture_layout_);
  main_layout_->addLayout(boxes_layout_);
  main_layout_->addLayout(buttons_layout_);
  picture_layout_->addWidget(left_);
  picture_layout_->addWidget(stacked_widget_, 0, Qt::AlignCenter);
  picture_layout_->addWidget(right_);
  boxes_layout_->addWidget(number_of_players_);
  boxes_layout_->addWidget(number_of_laps_);
  boxes_layout_->addWidget(number_of_bots_);
  buttons_layout_->addWidget(back_to_main_menu_);
  buttons_layout_->addWidget(start_game_);
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
          &GameModeSelector::StartGame);
  connect(back_to_main_menu_,
          &QPushButton::clicked,
          this,
          &GameModeSelector::ReturnToMainMenu);
  connect(number_of_players_,
          QOverload<int>::of(&QComboBox::currentIndexChanged),
          this,
          &GameModeSelector::ApplySettings);
  connect(number_of_laps_,
          QOverload<int>::of(&QComboBox::currentIndexChanged),
          this,
          &GameModeSelector::ApplySettings);
  connect(number_of_bots_,
          QOverload<int>::of(&QComboBox::currentIndexChanged),
          this,
          &GameModeSelector::ApplySettings);
}
