#include "pause_menu.h"

SmallExitWindow::SmallExitWindow(QWidget* parent)
    : QWidget(parent),
      main_widget_(new QWidget(this)),
      question_(new QLabel("Go to main menu?", main_widget_)),
      yes_button_(new QPushButton("YES", main_widget_)),
      no_button_(new QPushButton("NO", main_widget_)),
      width_(250),
      height_(100) {
  resize(width_, height_);
  main_widget_->resize(width_, height_);
  main_widget_->move(0, 0);
  question_->move(width_ * 3 / 10, height_ / 5);
  yes_button_->resize(width_ * 8 / 25, height_ * 2 / 5);
  yes_button_->move(width_ / 10, height_ * 2 / 5);
  no_button_->resize(width_ * 8 / 25, height_ * 2 / 5);
  no_button_->move(width_ * 29 / 50, height_ * 2 / 5);
}

PauseMenu::PauseMenu(QWidget* parent)
    : QWidget(parent),
      main_layout_(new QVBoxLayout(this)),
      settings_button_(new QPushButton("SETTINGS", this)),
      exit_button_(new QPushButton("MAIN MENU", this)),
      continue_button_(new QPushButton("CONTINUE", this)),
      small_exit_window_(new SmallExitWindow(this)),
      width_(500),
      height_(500) {
  resize(width_, height_);
  setStyleSheet("background-color : red");
  settings_button_->setMinimumSize(width_ * 3 / 5, height_ * 9 / 50);
  continue_button_->setMinimumSize(width_ * 3 / 5, height_ * 9 / 50);
  exit_button_->setMinimumSize(width_ * 3 / 5, height_ * 9 / 50);
  main_layout_->addStretch(5);
  main_layout_->addWidget(settings_button_, 1, Qt::AlignCenter);
  main_layout_->addWidget(continue_button_, 1, Qt::AlignCenter);
  main_layout_->addWidget(exit_button_, 1, Qt::AlignCenter);
  main_layout_->addStretch(5);
  small_exit_window_->setStyleSheet("background-color : yellow;"
                                    "color : darkBlue");
  small_exit_window_->close();
  connect(exit_button_, &QPushButton::clicked,
          small_exit_window_, &QWidget::show);
  connect(small_exit_window_->no_button_, &QPushButton::clicked,
          small_exit_window_, &QWidget::close);
}

void PauseMenu::resizeEvent(QResizeEvent*) {
  main_layout_->setGeometry(QRect(0, 0, width(), height()));
  small_exit_window_->move((width() - small_exit_window_->width_) / 2,
                           (height() - small_exit_window_->height_) / 2);
}
