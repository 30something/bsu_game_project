#include "settings.h"

Settings::Settings(GameMode* game_mode, QWidget* parent) :
    QWidget(parent),
    main_layout_(new QVBoxLayout(this)),
    manual_layout_(new QHBoxLayout),
    sliders_layout_(new QHBoxLayout),
    manual_(new QLabel(this)),
    music_(new QLabel("Music", this)),
    music_volume_(new QSlider(Qt::Horizontal, this)),
    sound_effects_(new QLabel("Sound Effects  ", this)),
    sound_effects_volume_(new QSlider(Qt::Horizontal, this)),
    full_screen_cell_(new QCheckBox("Full Screen")),
    apply_button_(new QPushButton("Apply", this)),
    back_button_(new QPushButton("Back", this)),
    game_mode_(game_mode) {
  SetManual();
  SetStyles();
  SetUpLayout();
  ConnectUI();
}

void Settings::SetManual() {
  manual_->setText(
      "\t           Keyboard manual\n\n"
      "First player car control - arrows (up, left, down, right)\n"
      "Second player car control - W, A, S, D\n"
      "First player puts mine - P\n"
      "First player shoots - O\n"
      "Second player puts mine - V\n"
      "Second player shoots - C");
}

void Settings::SetStyles() {
  setMinimumSize(menu_sizes::kSettingsSize);
  for (auto& widget : children()) {
    auto* label_ptr = qobject_cast<QLabel*>(widget);
    auto* button_ptr = qobject_cast<QPushButton*>(widget);
    auto* slider_ptr = qobject_cast<QSlider*>(widget);
    if (label_ptr) {
      label_ptr->setFont(fonts::kDefaultLabelFont);
      label_ptr->setStyleSheet("QLabel {"
                               "font: bold 25px; }");
    } else if (button_ptr) {
      button_ptr->setFont(fonts::kDefaultButtonFont);
      button_ptr->setMinimumSize(button_sizes::kDefaultButtonSize);
      button_ptr->setStyleSheet(styles::kStandardPushbuttonStyle);
    } else if (slider_ptr) {
      slider_ptr->setStyleSheet(styles::kStandardSliderStyle);
      slider_ptr->setMinimumSize(slider_sizes::kStandardSliderSizes);
    }
  }
  full_screen_cell_->setFont(fonts::kDefaultButtonFont);
  full_screen_cell_->setStyleSheet("QCheckBox {"
                                   "font: bold 25px; }");
  apply_button_->setMinimumSize(button_sizes::kSettingsMinButtonSize);
  back_button_->setMinimumSize(button_sizes::kSettingsMinButtonSize);
}

void Settings::SetUpLayout() {
  music_volume_->setValue(50);
  sound_effects_volume_->setValue(50);
  game_mode_->volume_settings_parameter = sound_effects_volume_->value();
  manual_layout_->addWidget(manual_, 1, Qt::AlignCenter);
  sliders_layout_->addStretch(2);
  sliders_layout_->addWidget(music_, 1, Qt::AlignCenter);
  sliders_layout_->addWidget(music_volume_, 1, Qt::AlignCenter);
  sliders_layout_->addStretch(1);
  sliders_layout_->addWidget(sound_effects_, 1, Qt::AlignCenter);
  sliders_layout_->addWidget(sound_effects_volume_, 1, Qt::AlignCenter);
  sliders_layout_->addStretch(2);
  main_layout_->addStretch(3);
  main_layout_->addLayout(manual_layout_);
  main_layout_->addStretch(2);
  main_layout_->addLayout(sliders_layout_);
  main_layout_->addStretch(3);
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
  game_mode_->volume_settings_parameter = sound_effects_volume_->value();
}
