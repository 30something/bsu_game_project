#include "settings.h"
#include "src/helpers/sizes.h"

Settings::Settings(QWidget* parent) :
    QWidget(parent),
    main_layout_(new QVBoxLayout(this)),
    music_layout_(new QHBoxLayout),
    sound_layout_(new QHBoxLayout),
    music_(new QLabel("Music", this)),
    music_volume_(new QSlider(Qt::Horizontal)),
    sound_effects_(new QLabel("Sound Effects", this)),
    sound_effects_volume_(new QSlider(Qt::Horizontal)),
    full_screen_cell_(new QCheckBox("Full Screen")),
    apply_button_(new QPushButton("Apply", this)),
    back_button_(new QPushButton("Back", this)) {
  SetFonts();
  SetSizes();
  SetUpLayout();
  ConnectUI();
}

void Settings::SetFonts() {
  music_->setFont(fonts::kDefaultLabelFont);
  sound_effects_->setFont(fonts::kDefaultLabelFont);
  full_screen_cell_->setFont(fonts::kDefaultButtonFont);
  apply_button_->setFont(fonts::kDefaultButtonFont);
  back_button_->setFont(fonts::kDefaultButtonFont);
}

void Settings::SetSizes() {
  setMinimumSize(menu_sizes::kSettingsSize);
  apply_button_->setMinimumSize(button_sizes::kSettingsMinButtonSize);
  back_button_->setMinimumSize(button_sizes::kSettingsMinButtonSize);
}

void Settings::SetUpLayout() {
  music_layout_->addStretch(2);
  music_layout_->addWidget(music_, 1, Qt::AlignCenter);
  music_layout_->addWidget(music_volume_, 1, Qt::AlignCenter);
  music_layout_->addStretch(2);
  sound_layout_->addStretch(2);
  sound_layout_->addWidget(sound_effects_, 1, Qt::AlignCenter);
  sound_layout_->addWidget(sound_effects_volume_, 1, Qt::AlignCenter);
  sound_layout_->addStretch(2);
  main_layout_->addStretch(3);
  main_layout_->addLayout(music_layout_);
  main_layout_->addStretch(2);
  main_layout_->addLayout(sound_layout_);
  main_layout_->addStretch(5);
  main_layout_->addWidget(full_screen_cell_, 2, Qt::AlignCenter);
  main_layout_->addWidget(apply_button_, 2, Qt::AlignCenter);
  main_layout_->addWidget(back_button_, 2, Qt::AlignCenter);
  main_layout_->addStretch(3);
}

void Settings::ConnectUI() {
  connect(back_button_,
          &QPushButton::clicked,
          this,
          &Settings::BackButtonPressed);
  connect(apply_button_,
          &QPushButton::clicked,
          this,
          &Settings::CommitSettingsChanges);
}

void Settings::CommitSettingsChanges() {
  if (full_screen_cell_->isChecked()) {
    emit MakeFullScreen();
  } else {
    emit MakeDefaultScreenSize();
  }
}
