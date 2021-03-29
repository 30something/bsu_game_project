#include "map_selector.h"

MapSelector::MapSelector(QWidget* parent) :
    QWidget(parent),
    start_game_(new QPushButton("Start", this)),
    back_to_main_menu_(new QPushButton("Back", this)),
    left_(new QPushButton("Previous", this)),
    right_(new QPushButton("Next", this)),
    layout_(new QHBoxLayout(this)),
    stacked_widget_(new QStackedWidget(this)) {
  for (const auto &i : map_data::map_filepaths) {
    stacked_widget_->addWidget(new MapSelectorTile(this, i.second));
  }
  MakeLayout();
  stacked_widget_->setCurrentIndex(0);
  DoConnects();
}

void MapSelector::SwitchRight() {
  if (current_id >= map_data::map_filepaths.size() - 1) {
    current_id = 0;
  } else {
    current_id++;
  }
  stacked_widget_->setCurrentIndex(current_id);
  repaint();
}

void MapSelector::SwitchLeft() {
  if (current_id <= 0) {
    current_id = map_data::map_filepaths.size() - 1;
  } else {
    current_id--;
  }
  stacked_widget_->setCurrentIndex(current_id);
  repaint();
}

uint MapSelector::GetMapId() const {
  return current_id;
}

void MapSelector::MakeLayout() {
  layout_->addWidget(back_to_main_menu_);
  layout_->addWidget(left_);
  layout_->addWidget(stacked_widget_, 0, Qt::AlignCenter);
  layout_->addWidget(right_);
  layout_->addWidget(start_game_);
}

void MapSelector::DoConnects() {
  connect(left_,
          &QPushButton::clicked,
          this,
          &MapSelector::SwitchLeft);
  connect(right_,
          &QPushButton::clicked,
          this,
          &MapSelector::SwitchRight);
  connect(start_game_,
          &QPushButton::clicked,
          this,
          &MapSelector::StartGame);
  connect(back_to_main_menu_,
          &QPushButton::clicked,
          this,
          &MapSelector::ReturnToMainMenu);
}
