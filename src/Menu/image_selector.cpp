#include "image_selector.h"

ImageSelector::ImageSelector(QWidget*,
                             GameMode* game_mode,
                             size_t player_number) :
    layout_(new QHBoxLayout(this)),
    left_(new QPushButton("Previous", this)),
    right_(new QPushButton("Next", this)),
    image_widget_(new QStackedWidget(this)),
    game_mode_(game_mode),
    player_number_(player_number) {
  InitializeInfo();
}

void ImageSelector::InitializeInfo() {
  setFont(fonts::kDefaultButtonFont);
  setStyleSheet(styles::kImageSelectorPushbuttonStyle);
  left_->setMinimumSize(button_sizes::kSmallChooseButtonSize);
  right_->setMinimumSize(button_sizes::kSmallChooseButtonSize);
  layout_->addWidget(left_, 1, Qt::AlignCenter);
  layout_->addWidget(image_widget_, 1, Qt::AlignCenter);
  layout_->addWidget(right_, 1, Qt::AlignCenter);
  connect(left_,
          &QPushButton::clicked,
          this,
          &ImageSelector::SwitchLeft);
  connect(right_,
          &QPushButton::clicked,
          this,
          &ImageSelector::SwitchRight);
}

void ImageSelector::InitializeImages(const QFileInfoList& images_list) {
  number_of_images_ = images_list.count();
  for (const auto& image : images_list) {
    image_widget_->addWidget(new ImageSelectorTile(image_widget_,
                                                   image.filePath()));
  }
  image_widget_->setCurrentIndex(0);
}

void ImageSelector::SwitchLeft() {
  if (player_number_ == 1) {
    if (game_mode_->first_player_car_number == 0) {
      game_mode_->first_player_car_number = number_of_images_ - 1;
    } else {
      game_mode_->first_player_car_number--;
    }
    image_widget_->setCurrentIndex(game_mode_->first_player_car_number);
  } else {
    if (game_mode_->second_player_car_number == 0) {
      game_mode_->second_player_car_number = number_of_images_ - 1;
    } else {
      game_mode_->second_player_car_number--;
    }
    image_widget_->setCurrentIndex(game_mode_->second_player_car_number);
  }
  repaint();
}

void ImageSelector::SwitchRight() {
  if (player_number_ == 1) {
    if (game_mode_->first_player_car_number >= number_of_images_ - 1) {
      game_mode_->first_player_car_number = 0;
    } else {
      game_mode_->first_player_car_number++;
    }
    image_widget_->setCurrentIndex(game_mode_->first_player_car_number);
  } else {
    if (game_mode_->second_player_car_number >= number_of_images_ - 1) {
      game_mode_->second_player_car_number = 0;
    } else {
      game_mode_->second_player_car_number++;
    }
    image_widget_->setCurrentIndex(game_mode_->second_player_car_number);
  }
  repaint();
}
