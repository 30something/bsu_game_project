#include "settings.h"
#include "src/helpers/sizes.h"

Settings::Settings(QWidget* parent) :
    QWidget(parent),
    main_layout_(new QVBoxLayout(this)),
    music_(new QLabel("Music", this)),
    music_volume_(new QSlider(Qt::Horizontal)),
    sound_effects_(new QLabel("Sound Effects", this)),
    sound_effects_volume_(new QSlider(Qt::Horizontal)),
    full_screen_cell_(new QRadioButton("Full Screen")),
    back_button_(new QPushButton("Back", this)) {
  setMinimumSize(menu_sizes::kSettingsSize);
  back_button_->setMinimumSize(menu_sizes::kSettingsMinButtonSize);

  main_layout_->addStretch(3);
  main_layout_->addWidget(music_, 1, Qt::AlignLeft);
  main_layout_->addWidget(music_volume_, 1, Qt::AlignCenter);
  main_layout_->addStretch(2);
  main_layout_->addWidget(sound_effects_, 1, Qt::AlignLeft);
  main_layout_->addWidget(sound_effects_volume_, 1, Qt::AlignCenter);
  main_layout_->addStretch(2);
  main_layout_->addWidget(full_screen_cell_, 1, Qt::AlignCenter);
  main_layout_->addStretch(2);
  main_layout_->addWidget(back_button_, 3, Qt::AlignCenter);
  main_layout_->addStretch(3);

  connect(back_button_, &QPushButton::clicked, this,
          &Settings::BackButtonPressed);
}
