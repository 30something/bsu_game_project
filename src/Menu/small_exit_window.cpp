#include "small_exit_window.h"

SmallExitWindow::SmallExitWindow(QWidget* parent)
    : QWidget(parent),
      main_widget_(new QWidget(this)),
      grid_layout_(new QGridLayout(this)),
      question_(new QLabel("Go to main menu?", main_widget_)),
      yes_button_(new QPushButton("YES", main_widget_)),
      no_button_(new QPushButton("NO", main_widget_)) {
  SetFonts();
  SetSizes();
  main_widget_->move(0, 0);
  SetUpLayout();
  ConnectUI();
}

void SmallExitWindow::SetFonts() {
  question_->setFont(fonts::kDefaultLabelFont);
  yes_button_->setFont(fonts::kDefaultButtonFont);
  no_button_->setFont(fonts::kDefaultButtonFont);
}

void SmallExitWindow::SetSizes() {
  resize(menu_sizes::kSmallExitWindowSize);
  main_widget_->resize(menu_sizes::kSmallExitWindowSize);
}

void SmallExitWindow::SetUpLayout() {
  grid_layout_->addWidget(question_, 0, 0, 1, 2, Qt::AlignCenter);
  grid_layout_->addWidget(yes_button_, 1, 0);
  grid_layout_->addWidget(no_button_, 1, 1);
}

void SmallExitWindow::ConnectUI() {
  connect(no_button_,
          &QPushButton::clicked,
          this,
          &SmallExitWindow::StayAtPauseMenu);
  connect(yes_button_,
          &QPushButton::clicked,
          this,
          &SmallExitWindow::ReturnToMainMenu);
}
