#include "menu.h"

Menu::Menu(QWidget* parent) :
    QWidget(parent),
    main_layout_(new QVBoxLayout(this)),
    name_label_(new QLabel("Survival Rally: Big Guns", this)),
    single_player_button_(new QPushButton("Singleplayer", this)),
    multi_player_button_(new QPushButton("Multiplayer", this)),
    settings_button_(new QPushButton("Settings", this)),
    credits_button_(new QPushButton("Credits", this)),
    exit_button_(new QPushButton("Exit", this)) {
  SetStyles();
  SetUpLayout();
  ConnectUI();
}

void Menu::SetStyles() {
  setMinimumSize(menu_sizes::kMenuSize);
  name_label_->setFont(fonts::kGameNameLabelFont);
  for (auto& widget : children()) {
    auto* button_ptr = qobject_cast<QPushButton*>(widget);
    if (button_ptr != nullptr) {
      button_ptr->setFont(fonts::kDefaultButtonFont);
      button_ptr->setMinimumSize(button_sizes::kDefaultButtonSize);
      button_ptr->setStyleSheet(styles::kStandardPushbuttonStyle);
    }
  }
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
