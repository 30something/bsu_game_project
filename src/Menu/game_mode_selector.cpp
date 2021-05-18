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
    cars_choose_layout_(new QVBoxLayout),
    first_player_label_(new QLabel("Choose first player's car:")),
    second_player_label_(new QLabel("Choose second player's car:")),
    first_left_(new QPushButton("Previous")),
    first_right_(new QPushButton("Next")),
    second_left_(new QPushButton("Previous")),
    second_right_(new QPushButton("Next")),
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
    first_car_stacked_widget_(new QStackedWidget(this)),
    second_car_stacked_widget_(new QStackedWidget(this)),
    game_mode_(game_mode),
    number_of_players_(new QComboBox(this)),
    number_of_laps_(new QComboBox(this)),
    number_of_bots_(new QComboBox(this)) {
  number_of_maps_pixmaps_ =
      map_data::image_file_paths.minimaps_file_paths.size();
  for (const auto& image : map_data::image_file_paths.minimaps_file_paths) {
    map_stacked_widget_->addWidget(new MapSelectorTile(map_stacked_widget_,
                                                       image));
  }
  QFileInfoList standard_cars_list =
      QDir(":resources/images/cars/standard_cars").entryInfoList();
  number_of_cars_pixmaps_ = standard_cars_list.count();
  for (const auto& image : standard_cars_list) {
    first_car_stacked_widget_->addWidget(new ImageSelectorTile(
        first_car_stacked_widget_,
        image.filePath()));
    second_car_stacked_widget_->addWidget(new ImageSelectorTile(
        second_car_stacked_widget_,
        image.filePath()));
  }
  SetFonts();
  SetSizes();
  PrepareComboBoxes();
  SetUpLayouts();
  map_stacked_widget_->setCurrentIndex(0);
  first_car_stacked_widget_->setCurrentIndex(0);
  second_car_stacked_widget_->setCurrentIndex(0);
  second_car_stacked_widget_->hide();
  ConnectUI();
}

void GameModeSelector::resizeEvent(QResizeEvent*) {
  map_stacked_widget_->setGeometry(width() / kMinimapStartXDivisionCoef,
                                   height() / kMinimapStartYDivisionCoef,
                                   width() / kMinimapWidthDivisionCoef,
                                   height() / kMinimapHeightDivisionCoef);
}

void GameModeSelector::SetFonts() {
  first_player_label_->setFont(fonts::kDefaultLabelFont);
  second_player_label_->setFont(fonts::kDefaultLabelFont);
  players_label_->setFont(fonts::kDefaultLabelFont);
  laps_label_->setFont(fonts::kDefaultLabelFont);
  bots_label_->setFont(fonts::kDefaultLabelFont);
  start_game_->setFont(fonts::kDefaultButtonFont);
  back_to_main_menu_->setFont(fonts::kDefaultButtonFont);
  left_->setFont(fonts::kDefaultButtonFont);
  right_->setFont(fonts::kDefaultButtonFont);
  first_left_->setFont(fonts::kDefaultButtonFont);
  first_right_->setFont(fonts::kDefaultButtonFont);
  second_left_->setFont(fonts::kDefaultButtonFont);
  second_right_->setFont(fonts::kDefaultButtonFont);
  enable_drifts_->setFont(fonts::kDefaultButtonFont);
  number_of_players_->setFont(fonts::kDefaultButtonFont);
  number_of_laps_->setFont(fonts::kDefaultButtonFont);
  number_of_bots_->setFont(fonts::kDefaultButtonFont);
}

void GameModeSelector::SetSizes() {
  start_game_->setMinimumSize(button_sizes::kDefaultButtonSize);
  back_to_main_menu_->setMinimumSize(button_sizes::kDefaultButtonSize);
  left_->setMinimumSize(button_sizes::kMapSelectorsSize);
  right_->setMinimumSize(button_sizes::kMapSelectorsSize);
  first_left_->setMinimumSize(button_sizes::kSmallChooseButtonSize);
  first_right_->setMinimumSize(button_sizes::kSmallChooseButtonSize);
  second_left_->setMinimumSize(button_sizes::kSmallChooseButtonSize);
  second_right_->setMinimumSize(button_sizes::kSmallChooseButtonSize);
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

void GameModeSelector::SwitchMapLeft() {
  if (game_mode_->map_index == 0) {
    game_mode_->map_index = number_of_maps_pixmaps_ - 1;
  } else {
    game_mode_->map_index--;
  }
  map_stacked_widget_->setCurrentIndex(game_mode_->map_index);
  repaint();
}

void GameModeSelector::SwitchMapRight() {
  if (game_mode_->map_index >= number_of_maps_pixmaps_ - 1) {
    game_mode_->map_index = 0;
  } else {
    game_mode_->map_index++;
  }
  map_stacked_widget_->setCurrentIndex(game_mode_->map_index);
  repaint();
}

void GameModeSelector::SwitchFirstCarLeft() {
  if (game_mode_->first_player_car_number == 0) {
    game_mode_->first_player_car_number = number_of_cars_pixmaps_ - 1;
  } else {
    game_mode_->first_player_car_number--;
  }
  first_car_stacked_widget_->setCurrentIndex(
      game_mode_->first_player_car_number);
  repaint();
}

void GameModeSelector::SwitchFirstCarRight() {
  if (game_mode_->first_player_car_number >= number_of_cars_pixmaps_ - 1) {
    game_mode_->first_player_car_number = 0;
  } else {
    game_mode_->first_player_car_number++;
  }
  first_car_stacked_widget_->setCurrentIndex(
      game_mode_->first_player_car_number);
  repaint();
}

void GameModeSelector::SwitchSecondCarLeft() {
  if (game_mode_->second_player_car_number == 0) {
    game_mode_->second_player_car_number = number_of_cars_pixmaps_ - 1;
  } else {
    game_mode_->second_player_car_number--;
  }
  second_car_stacked_widget_->setCurrentIndex(
      game_mode_->second_player_car_number);
  repaint();
}

void GameModeSelector::SwitchSecondCarRight() {
  if (game_mode_->second_player_car_number >= number_of_cars_pixmaps_ - 1) {
    game_mode_->second_player_car_number = 0;
  } else {
    game_mode_->second_player_car_number++;
  }
  second_car_stacked_widget_->setCurrentIndex(
      game_mode_->second_player_car_number);
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
    second_left_->show();
    second_car_stacked_widget_->show();
    second_right_->show();
  } else {
    cars_choose_layout_->removeItem(second_player_info_layout_);
    second_player_label_->hide();
    second_right_->hide();
    second_car_stacked_widget_->hide();
    second_left_->hide();
  }
}

void GameModeSelector::SetUpLayouts() {
  main_layout_->addStretch(10);
  main_layout_->addLayout(picture_layout_);
  main_layout_->addStretch(20);
  main_layout_->addLayout(cars_choose_layout_);
  main_layout_->addLayout(boxes_layout_);
  main_layout_->addStretch(1);
  main_layout_->addLayout(buttons_layout_);
  picture_layout_->addWidget(left_, 1, Qt::AlignCenter);
  picture_layout_->addStretch(1);
  picture_layout_->addWidget(right_, 1, Qt::AlignCenter);
  cars_choose_layout_->addLayout(first_player_info_layout_);
  first_player_info_layout_->addStretch(3);
  first_player_info_layout_->addWidget(first_player_label_, 1, Qt::AlignCenter);
  first_player_info_layout_->addWidget(first_left_, 1, Qt::AlignCenter);
  first_player_info_layout_->addWidget(first_car_stacked_widget_);
  first_player_info_layout_->addWidget(first_right_, 1, Qt::AlignCenter);
  first_player_info_layout_->addStretch(3);
  second_player_info_layout_->addStretch(3);
  second_player_info_layout_->addWidget(second_player_label_, 1,
                                        Qt::AlignCenter);
  second_player_info_layout_->addWidget(second_left_, 1, Qt::AlignCenter);
  second_player_info_layout_->addWidget(second_car_stacked_widget_);
  second_player_info_layout_->addWidget(second_right_, 1, Qt::AlignCenter);
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
  connect(first_left_,
          &QPushButton::clicked,
          this,
          &GameModeSelector::SwitchFirstCarLeft);
  connect(first_right_,
          &QPushButton::clicked,
          this,
          &GameModeSelector::SwitchFirstCarRight);
  connect(second_left_,
          &QPushButton::clicked,
          this,
          &GameModeSelector::SwitchSecondCarLeft);
  connect(second_right_,
          &QPushButton::clicked,
          this,
          &GameModeSelector::SwitchSecondCarRight);
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
