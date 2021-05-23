#include "settings.h"
#include "src/helpers/sizes.h"

Settings::Settings(QWidget* parent) :
    QWidget(parent),
    main_layout_(new QVBoxLayout(this)),
    music_layout_(new QHBoxLayout),
    sound_layout_(new QHBoxLayout),
    music_(new QLabel("Music", this)),
    music_volume_(new QSlider(Qt::Horizontal, this)),
    sound_effects_(new QLabel("Sound Effects", this)),
    sound_effects_volume_(new QSlider(Qt::Horizontal, this)),
    full_screen_cell_(new QCheckBox("Full Screen")),
    apply_button_(new QPushButton("Apply", this)),
    back_button_(new QPushButton("Back", this)) {
  SetStyles();
  SetUpLayout();
  ConnectUI();
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
    } else if (slider_ptr) {
      slider_ptr->setStyleSheet("QSlider::groove:horizontal {"
                                "border: 1px solid #999999;"
                                "height: 8px;"
                                "background: qlineargradient(x1:0, y1:0, x2:0, "
                                "y2:1, stop:0 #B1B1B1, stop:1 #c4c4c4);"
                                "margin: 2px 0; }"

                                "QSlider::handle:horizontal {"
                                "background: qlineargradient(x1:0, y1:0, x2:1, "
                                "y2:1, stop:0 #b4b4b4, stop:1 #8f8f8f);"
                                "border: 1px solid #5c5c5c;"
                                "width: 18px;"
                                "margin: -2px 0;"
                                "border-radius: 3px; }");
    }
  }
  full_screen_cell_->setFont(fonts::kDefaultButtonFont);
  full_screen_cell_->setStyleSheet("QCheckBox {"
                                "font: bold 16px; }");
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
