#include "pause_menu.h"

SmallExitWindow::SmallExitWindow(QWidget *parent)
    : parent_(parent),
      width_(250),
      height_(100),
      question_(new QLabel("Go to main menu?", this)),
      yes_button_(new QPushButton("YES", this)),
      no_button_(new QPushButton("NO", this)) {
  setWindowFlags(Qt::FramelessWindowHint);
  resize(width_, height_);
  setStyleSheet("background-color : yellow");
  setStyleSheet("color : pink");
  question_->move(width_ * 3 / 10, height_ / 5);
  yes_button_->resize(width_ * 8 / 25, height_ * 2 / 5);
  yes_button_->move(width_ / 10, height_ * 2 / 5);
  no_button_->resize(width_ * 8 / 25, height_ * 2 / 5);
  no_button_->move(width_ * 29 / 50, height_ * 2 / 5);
}

PauseMenu::PauseMenu(QWidget *parent)
    : parent_(parent),
      width_(500),
      height_(500),
      settings_button_(new QPushButton("SETTINGS", this)),
      exit_button_(new QPushButton("MAIN MENU", this)),
      continue_button_(new QPushButton("CONTINUE", this)),
      stacked_widget_(new QStackedWidget(this)),
      small_exit_window_(new SmallExitWindow(stacked_widget_)) {
  setWindowFlags(Qt::FramelessWindowHint);
  resize(width_, height_);
  setStyleSheet("background-color : red");
  small_exit_window_->setStyleSheet("color : darkBlue");
  stacked_widget_->setStyleSheet("background-color : yellow;");
  settings_button_->resize(width_ * 3 / 5, height_ * 9 / 50);
  settings_button_->move(width_ / 5, height_ / 5);
  continue_button_->resize(width_ * 3 / 5, height_ * 9 / 50);
  continue_button_->move(width_ / 5, height_ * 2 / 5);
  exit_button_->resize(width_ * 3 / 5, height_ * 9 / 50);
  exit_button_->move(width_ / 5, height_ * 3 / 5);
  stacked_widget_->resize(width_ / 2, height_ / 5);
  stacked_widget_->move(width_ / 4, height_ * 2 / 5);
  stacked_widget_->addWidget(small_exit_window_);
  stacked_widget_->close();
  connect(exit_button_, &QPushButton::clicked,
          stacked_widget_, &QStackedWidget::show);
  connect(small_exit_window_->no_button_, &QPushButton::clicked,
          stacked_widget_, &QStackedWidget::close);
}

int PauseMenu::GetWidth() const {
  return width_;
}

int PauseMenu::GetHeight() const {
  return height_;
}
