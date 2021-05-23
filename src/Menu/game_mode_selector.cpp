#include "game_mode_selector.h"

GameModeSelector::GameModeSelector(QWidget* parent, GameMode* game_mode) :
    QWidget(parent),
    start_game_(new QPushButton("Start", this)),
    back_to_main_menu_(new QPushButton("Back", this)),
    left_(new QPushButton("Previous", this)),
    right_(new QPushButton("Next", this)),
    main_layout_(new QVBoxLayout(this)),
    picture_layout_(new QHBoxLayout),
    cars_choose_layout_(new QVBoxLayout),
    first_player_label_(new QLabel("Choose first player's car:", this)),
    second_player_label_(new QLabel("Choose second player's car:", this)),
    first_player_info_layout_(new QHBoxLayout),
    second_player_info_layout_(new QHBoxLayout),
    players_label_(new QLabel("Choose number of players: ", this)),
    laps_label_(new QLabel("Choose number of laps: ", this)),
    bots_label_(new QLabel("Choose number of bots: ", this)),
    enable_drifts_(new QCheckBox("Enable Drifts?", this)),
    players_layout_(new QHBoxLayout),
    laps_layout_(new QHBoxLayout),
    bots_layout_(new QHBoxLayout),
    boxes_layout_(new QVBoxLayout),
    buttons_layout_(new QHBoxLayout),
    map_stacked_widget_(new QStackedWidget(this)),
    game_mode_(game_mode),
    first_car_selector_(new ImageSelector(this, game_mode_)),
    second_car_selector_(new ImageSelector(this, game_mode_)),
    number_of_players_(new QComboBox(this)),
    number_of_laps_(new QComboBox(this)),
    number_of_bots_(new QComboBox(this)) {
  InitializeImages();
  SetStyles();
  PrepareComboBoxes();
  SetUpLayouts();
  ConnectUI();
}

void GameModeSelector::resizeEvent(QResizeEvent*) {
  map_stacked_widget_->setGeometry(width() / kMinimapStartXDivisionCoef,
                                   height() / kMinimapStartYDivisionCoef,
                                   width() / kMinimapWidthDivisionCoef,
                                   static_cast<int>(static_cast<double>
                                   (height()) / kMinimapHeightDivisionCoef));
}

void GameModeSelector::InitializeImages() {
  number_of_maps_pixmaps_ =
      map_data::image_file_paths.minimaps_file_paths.size();
  for (const auto& image : map_data::image_file_paths.minimaps_file_paths) {
    map_stacked_widget_->addWidget(new MapSelectorTile(map_stacked_widget_,
                                                       image));
  }
  QFileInfoList standard_cars_list =
      QDir(":resources/images/cars/cars_icons").entryInfoList();
  first_car_selector_->InitializeImages(standard_cars_list);
  second_car_selector_->InitializeImages(standard_cars_list);
  map_stacked_widget_->setCurrentIndex(0);
  second_car_selector_->hide();
  second_player_label_->hide();
}

void GameModeSelector::SetStyles() {
  for (auto& widget : children()) {
    auto* label_ptr = qobject_cast<QLabel*>(widget);
    auto* button_ptr = qobject_cast<QPushButton*>(widget);
    auto* combo_box_ptr = qobject_cast<QComboBox*>(widget);
    if (label_ptr) {
      label_ptr->setFont(fonts::kDefaultLabelFont);
      label_ptr->setStyleSheet("QLabel {"
                               "font: bold 18px; }");
    } else if (button_ptr) {
      button_ptr->setFont(fonts::kDefaultButtonFont);
      button_ptr->setMinimumSize(button_sizes::kDefaultButtonSize);
      button_ptr->setStyleSheet("QPushButton {"
                                "background-color: #ff9900;"
                                "border-style: outset;"
                                "border-width: 2px;"
                                "border-radius: 10px;"
                                "border-color: beige;"
                                "font: bold 18px; }"

                                "QPushButton::pressed {"
                                "background-color: #e68a00;"
                                "border-style: inset; }");
    } else if (combo_box_ptr) {
      combo_box_ptr->setFont(fonts::kDefaultButtonFont);
      combo_box_ptr->setMinimumSize(combo_boxes_sizes::kComboBoxDefaultSize);
      combo_box_ptr->setStyleSheet("QComboBox {"
                                   "background-color: #ff9900;"
                                   "border-style: outset;"
                                   "border-width: 2px;"
                                   "border-radius: 10px;"
                                   "border-color: beige;"
                                   "padding: 5px;"
                                   "font: bold 18px; }"

                                   "QComboBox::drop-down {"
                                   "border-width: 0px; }"

                                   "QComboBox::down-arrow {"
                                   "border-width: 0px; }");
    }
  }
  enable_drifts_->setFont(fonts::kDefaultButtonFont);
  enable_drifts_->setStyleSheet("QCheckBox {"
                                "font: bold 16px; }");
  left_->setMinimumSize(button_sizes::kMapSelectorsSize);
  right_->setMinimumSize(button_sizes::kMapSelectorsSize);
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

void GameModeSelector::SwitchMapLeft() {
  if (game_mode_->map_index == 0) {
    game_mode_->map_index = number_of_maps_pixmaps_ - 1;
  } else {
    game_mode_->map_index--;
  }
  map_stacked_widget_->setCurrentIndex(static_cast<int>(game_mode_->map_index));
  repaint();
}

void GameModeSelector::SwitchMapRight() {
  if (game_mode_->map_index >= number_of_maps_pixmaps_ - 1) {
    game_mode_->map_index = 0;
  } else {
    game_mode_->map_index++;
  }
  map_stacked_widget_->setCurrentIndex(static_cast<int>(game_mode_->map_index));
  repaint();
}

void GameModeSelector::ApplySettings() {
  game_mode_->players_amount = number_of_players_->currentIndex() + 1;
  game_mode_->laps_amount = number_of_laps_->currentIndex() + 1;
  game_mode_->bots_amount = number_of_bots_->currentIndex();
  game_mode_->enable_drifting = enable_drifts_->isChecked();
}

void GameModeSelector::ApplyPlayersSettings() {
  if (cars_choose_layout_->count() == 1) {
    cars_choose_layout_->addLayout(second_player_info_layout_);
    second_player_label_->show();
    second_car_selector_->show();
  } else {
    cars_choose_layout_->removeItem(second_player_info_layout_);
    second_player_label_->hide();
    second_car_selector_->hide();
  }
}

void GameModeSelector::SetUpLayouts() {
  main_layout_->addStretch(10);
  main_layout_->addLayout(picture_layout_);
  main_layout_->addStretch(20);
  main_layout_->addLayout(cars_choose_layout_);
  main_layout_->addStretch(1);
  main_layout_->addLayout(boxes_layout_);
  main_layout_->addStretch(1);
  main_layout_->addLayout(buttons_layout_);
  picture_layout_->addWidget(left_, 1, Qt::AlignCenter);
  picture_layout_->addStretch(1);
  picture_layout_->addWidget(right_, 1, Qt::AlignCenter);
  cars_choose_layout_->addLayout(first_player_info_layout_);
  first_player_info_layout_->addStretch(3);
  first_player_info_layout_->addWidget(first_player_label_, 1, Qt::AlignCenter);
  first_player_info_layout_->addWidget(first_car_selector_, 1, Qt::AlignCenter);
  first_player_info_layout_->addStretch(3);
  second_player_info_layout_->addStretch(3);
  second_player_info_layout_->addWidget(second_player_label_, 1,
                                        Qt::AlignCenter);
  second_player_info_layout_->addWidget(second_car_selector_, 1,
                                        Qt::AlignCenter);
  second_player_info_layout_->addStretch(3);
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
  boxes_layout_->addWidget(enable_drifts_, 1, Qt::AlignCenter);
  buttons_layout_->addWidget(back_to_main_menu_, Qt::AlignCenter);
  buttons_layout_->addWidget(start_game_, Qt::AlignCenter);
}

void GameModeSelector::ConnectUI() {
  connect(left_,
          &QPushButton::clicked,
          this,
          &GameModeSelector::SwitchMapLeft);
  connect(right_,
          &QPushButton::clicked,
          this,
          &GameModeSelector::SwitchMapRight);
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
  connect(number_of_players_,
          QOverload<int>::of(&QComboBox::currentIndexChanged),
          this,
          &GameModeSelector::ApplyPlayersSettings);
  connect(number_of_laps_,
          QOverload<int>::of(&QComboBox::currentIndexChanged),
          this,
          &GameModeSelector::ApplySettings);
  connect(number_of_bots_,
          QOverload<int>::of(&QComboBox::currentIndexChanged),
          this,
          &GameModeSelector::ApplySettings);
  connect(enable_drifts_,
          &QCheckBox::stateChanged,
          this,
          &GameModeSelector::ApplySettings);
}
