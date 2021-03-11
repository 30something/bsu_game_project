#include "pause_menu.h"

SmallExitWindow::SmallExitWindow(QWidget *parent)
    : width_(250),
      height_(100),
      main_widget_(new QWidget(this)),
      question_(new QLabel("Go to main menu?", main_widget_)),
      yes_button_(new QPushButton("YES", main_widget_)),
      no_button_(new QPushButton("NO", main_widget_)) {
  setParent(parent);
  resize(width_, height_);
  main_widget_->resize(width_, height_);
  main_widget_->move(0, 0);
  question_->move(width_ * 3 / 10, height_ / 5);
  yes_button_->resize(width_ * 8 / 25, height_ * 2 / 5);
  yes_button_->move(width_ / 10, height_ * 2 / 5);
  no_button_->resize(width_ * 8 / 25, height_ * 2 / 5);
  no_button_->move(width_ * 29 / 50, height_ * 2 / 5);
}

PauseMenu::PauseMenu(QWidget *parent)
    : width_(500),
      height_(500),
      settings_button_(new QPushButton("SETTINGS", this)),
      exit_button_(new QPushButton("MAIN MENU", this)),
      continue_button_(new QPushButton("CONTINUE", this)),
      small_exit_window_(new SmallExitWindow(this)) {
  setParent(parent);
  resize(width_, height_);
  setStyleSheet("background-color : red");
  settings_button_->resize(width_ * 3 / 5, height_ * 9 / 50);
  settings_button_->move(width_ / 5, height_ / 5);
  continue_button_->resize(width_ * 3 / 5, height_ * 9 / 50);
  continue_button_->move(width_ / 5, height_ * 2 / 5);
  exit_button_->resize(width_ * 3 / 5, height_ * 9 / 50);
  exit_button_->move(width_ / 5, height_ * 3 / 5);
  small_exit_window_->resize(width_ / 2, height_ / 5);
  small_exit_window_->setStyleSheet("background-color : yellow;"
                                    "color : darkBlue");
  small_exit_window_->move(width_ / 4, height_ * 2 / 5);
  small_exit_window_->close();
  connect(exit_button_, &QPushButton::clicked,
          small_exit_window_, &QWidget::show);
  connect(small_exit_window_->no_button_, &QPushButton::clicked,
          small_exit_window_, &QWidget::close);
}
