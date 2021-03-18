#include "small_exit_window.h"

SmallExitWindow::SmallExitWindow(QWidget* parent)
    : QWidget(parent),
      main_widget_(new QWidget(this)),
      question_(new QLabel("Go to main menu?", main_widget_)),
      yes_button_(new QPushButton("YES", main_widget_)),
      no_button_(new QPushButton("NO", main_widget_)) {
  resize(width_, height_);
  main_widget_->resize(width_, height_);
  main_widget_->move(0, 0);
  question_->move(width_ * 3 / 10, height_ / 5);
  yes_button_->resize(width_ * 8 / 25, height_ * 2 / 5);
  yes_button_->move(width_ / 10, height_ * 2 / 5);
  no_button_->resize(width_ * 8 / 25, height_ * 2 / 5);
  no_button_->move(width_ * 29 / 50, height_ * 2 / 5);
}

QPushButton* SmallExitWindow::GetYesButton() const {
  return yes_button_;
}

QPushButton* SmallExitWindow::GetNoButton() const {
  return no_button_;
}

int SmallExitWindow::GetWidth() const {
  return width_;
}

int SmallExitWindow::GetHeight() const {
  return height_;
}
