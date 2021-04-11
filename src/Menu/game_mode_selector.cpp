#include "game_mode_selector.h"
#include "src/helpers/sizes.h"

GameModeSelector::GameModeSelector(QWidget* parent, GameMode* game_mode) :
    QWidget(parent),
    start_game_(new QPushButton("Start", this)),
    back_to_main_menu_(new QPushButton("Back", this)),
    left_(new QPushButton("Previous", this)),
    right_(new QPushButton("Next", this)),
    main_layout_(new QVBoxLayout(this)),
    picture_layout_(new QHBoxLayout),
    players_label_(new QLabel("Choose number of players: ", this)),
    laps_label_(new QLabel("Choose number of laps: ", this)),
    bots_label_(new QLabel("Choose number of bots: ", this)),
    players_layout_(new QHBoxLayout),
    laps_layout_(new QHBoxLayout),
    bots_layout_(new QHBoxLayout),
    boxes_layout_(new QVBoxLayout),
    buttons_layout_(new QHBoxLayout),
    stacked_widget_(new QStackedWidget(this)),
    game_mode_(game_mode),
    number_of_players_(new QComboBox(this)),
    number_of_laps_(new QComboBox(this)),
    number_of_bots_(new QComboBox(this)) {
  for (const auto& image : map_data::image_filepaths) {
    stacked_widget_->addWidget(new MapSelectorTile(this, image));
  }
  SetSizes();
  PrepareComboBoxes();
  SetUpLayouts();
  stacked_widget_->setCurrentIndex(0);
  ConnectUI();
}

void GameModeSelector::SetSizes() {
  start_game_->setMinimumSize(button_sizes::kDefaultButtonSize);
  back_to_main_menu_->setMinimumSize(button_sizes::kDefaultButtonSize);
  left_->setMinimumSize(button_sizes::kMapSelectorsSize);
  right_->setMinimumSize(button_sizes::kMapSelectorsSize);
  number_of_players_->setMinimumSize(combo_boxes_sizes::kComboBoxDefaultSize);
  number_of_laps_->setMinimumSize(combo_boxes_sizes::kComboBoxDefaultSize);
  number_of_bots_->setMinimumSize(combo_boxes_sizes::kComboBoxDefaultSize);
}

void GameModeSelector::PrepareComboBoxes() {
  for (size_t i = 1; i <= kMaxPlayersAmount; i++) {
    number_of_players_->addItem(QString::number(i));
  }
  for (size_t i = 0; i <= kMaxBotsAmount; i++) {
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
  game_mode_->bots_amount = number_of_bots_->currentIndex();
}

void GameModeSelector::SetUpLayouts() {
  main_layout_->addLayout(picture_layout_);
  main_layout_->addLayout(boxes_layout_);
  main_layout_->addLayout(buttons_layout_);
  picture_layout_->addWidget(left_, 1, Qt::AlignCenter);
  picture_layout_->addWidget(stacked_widget_, 0, Qt::AlignCenter);
  picture_layout_->addWidget(right_, 1, Qt::AlignCenter);
  players_layout_->addStretch(2);
  players_layout_->addWidget(players_label_, 1, Qt::AlignCenter);
  players_layout_->addWidget(number_of_players_, 1, Qt::AlignCenter);
  players_layout_->addStretch(2);
  laps_layout_->addStretch(2);
  laps_layout_->addWidget(laps_label_, 1, Qt::AlignCenter);
  laps_layout_->addWidget(number_of_laps_, 1, Qt::AlignCenter);
  laps_layout_->addStretch(2);
  bots_layout_->addStretch(2);
  bots_layout_->addWidget(bots_label_, 1, Qt::AlignCenter);
  bots_layout_->addWidget(number_of_bots_, 1, Qt::AlignCenter);
  bots_layout_->addStretch(2);
  boxes_layout_->addLayout(players_layout_);
  boxes_layout_->addLayout(laps_layout_);
  boxes_layout_->addLayout(bots_layout_);
  buttons_layout_->addWidget(back_to_main_menu_, Qt::AlignCenter);
  buttons_layout_->addWidget(start_game_, Qt::AlignCenter);
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
