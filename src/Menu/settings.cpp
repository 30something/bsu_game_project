#include "settings.h"
#include "src/helpers/sizes.h"

Settings::Settings(QWidget* parent) :
    QWidget(parent),
    main_layout_(new QVBoxLayout(this)),
    music_(new QLabel("Music", this)),
    music_volume_(new QSlider(Qt::Horizontal)),
    sound_effects_(new QLabel("Sound Effects", this)),
    sound_effects_volume_(new QSlider(Qt::Horizontal)),
    full_screen_cell_(new QCheckBox("Full Screen")),
    apply_button_(new QPushButton("Apply", this)),
    back_button_(new QPushButton("Back", this)) {
  SetSizes();
  SetUpLayout();
  ConnectUI();
}

void Settings::SetSizes() {
  setMinimumSize(menu_sizes::kSettingsSize);
  apply_button_->setMinimumSize(menu_sizes::kSettingsMinButtonSize);
  back_button_->setMinimumSize(menu_sizes::kSettingsMinButtonSize);
}

void Settings::SetUpLayout() {
  main_layout_->addStretch(3);
  main_layout_->addWidget(music_, 1, Qt::AlignLeft);
  main_layout_->addWidget(music_volume_, 1, Qt::AlignCenter);
  main_layout_->addStretch(2);
  main_layout_->addWidget(sound_effects_, 1, Qt::AlignLeft);
  main_layout_->addWidget(sound_effects_volume_, 1, Qt::AlignCenter);
  main_layout_->addStretch(2);
  main_layout_->addWidget(full_screen_cell_, 1, Qt::AlignCenter);
  main_layout_->addStretch(2);
  main_layout_->addWidget(apply_button_, 3, Qt::AlignCenter);
  main_layout_->addStretch(2);
  main_layout_->addWidget(back_button_, 3, Qt::AlignCenter);
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
