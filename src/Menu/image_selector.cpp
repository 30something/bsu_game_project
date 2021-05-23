#include "image_selector.h"

ImageSelector::ImageSelector(QWidget*, GameMode* game_mode) :
    layout_(new QHBoxLayout(this)),
    left_(new QPushButton("Previous", this)),
    right_(new QPushButton("Next", this)),
    image_widget_(new QStackedWidget(this)),
    game_mode_(game_mode) {
  InitializeInfo();
}

void ImageSelector::InitializeInfo() {
  setFont(fonts::kDefaultButtonFont);
  setStyleSheet("QPushButton {"
                "background-color: #ff9900;"
                "border-style: outset;"
                "border-width: 2px;"
                "border-radius: 10px;"
                "border-color: beige;"
                "padding: 2px;"
                "font: bold 14px; }"

                "QPushButton::pressed {"
                "background-color: #e68a00;"
                "border-style: inset; }");
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
  if (game_mode_->first_player_car_number == 0) {
    game_mode_->first_player_car_number = number_of_images_ - 1;
  } else {
    game_mode_->first_player_car_number--;
  }
  image_widget_->setCurrentIndex(game_mode_->first_player_car_number);
  repaint();
}

void ImageSelector::SwitchRight() {
  if (game_mode_->first_player_car_number >= number_of_images_ - 1) {
    game_mode_->first_player_car_number = 0;
  } else {
    game_mode_->first_player_car_number++;
  }
  image_widget_->setCurrentIndex(game_mode_->first_player_car_number);
  repaint();
}
