#include "menu.h"
#include "src/helpers/sizes.h"

Menu::Menu(QWidget* parent) :
    QWidget(parent),
    main_layout_(new QVBoxLayout(this)),
    name_label_(new QLabel("Death Rally", this)),
    single_player_button_(new QPushButton("Single player", this)),
    multi_player_button_(new QPushButton("Multi player", this)),
    settings_button_(new QPushButton("Settings", this)),
    credits_button_(new QPushButton("Credits", this)),
    exit_button_(new QPushButton("Exit", this)) {
  SetSizes();
  SetUpLayout();
  ConnectUI();
}

void Menu::SetSizes() {
  setMinimumSize(menu_sizes::kMenuSize);
  single_player_button_->setMinimumSize(button_sizes::kDefaultButtonSize);
  multi_player_button_->setMinimumSize(button_sizes::kDefaultButtonSize);
  settings_button_->setMinimumSize(button_sizes::kDefaultButtonSize);
  credits_button_->setMinimumSize(button_sizes::kDefaultButtonSize);
  exit_button_->setMinimumSize(button_sizes::kDefaultButtonSize);
}

void Menu::SetUpLayout() {
  main_layout_->setSpacing(menu_sizes::kMenuSpacing);
  main_layout_->addStretch(5);
  main_layout_->addWidget(name_label_, 1, Qt::AlignCenter);
  main_layout_->addStretch(5);
  main_layout_->addWidget(single_player_button_, 1, Qt::AlignCenter);
  main_layout_->addWidget(multi_player_button_, 1, Qt::AlignCenter);
  main_layout_->addWidget(settings_button_, 1, Qt::AlignCenter);
  main_layout_->addWidget(credits_button_, 1, Qt::AlignCenter);
  main_layout_->addWidget(exit_button_, 1, Qt::AlignCenter);
  main_layout_->addStretch(5);
}

void Menu::ConnectUI() {
  connect(single_player_button_,
          &QPushButton::clicked,
          this,
          &Menu::SinglePlayerPressed);
  connect(multi_player_button_,
          &QPushButton::clicked,
          this,
          &Menu::MultiPlayerPressed);
  connect(settings_button_,
          &QPushButton::clicked,
          this,
          &Menu::SettingsButtonPressed);
  connect(exit_button_,
          &QPushButton::clicked,
          this,
          &Menu::ExitButtonPressed);
}
