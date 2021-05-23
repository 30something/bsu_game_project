#include "pause_menu.h"

PauseMenu::PauseMenu(QWidget* parent)
    : QWidget(parent),
      main_layout_(new QVBoxLayout(this)),
      settings_button_(new QPushButton("Settings", this)),
      exit_button_(new QPushButton("Main menu", this)),
      continue_button_(new QPushButton("Continue", this)),
      small_exit_window_(new SmallExitWindow(this)) {
  SetStyles();
  SetUpLayout();
  small_exit_window_->setStyleSheet("background-color : yellow;"
                                    "color : darkBlue");
  small_exit_window_->close();
  ConnectUI();
}

void PauseMenu::resizeEvent(QResizeEvent*) {
  small_exit_window_->move(
      (width() - menu_sizes::kSmallExitWindowSize.width())
          / menu_sizes::kSmallExitWindowMoveCoef,
      (height() - menu_sizes::kSmallExitWindowSize.height())
          / menu_sizes::kSmallExitWindowMoveCoef);
}

void PauseMenu::keyPressEvent(QKeyEvent* event) {
  if (event->key() == static_cast<int>(Actions::kCloseMenu)) {
    emit ContinueGame();
  }
}

void PauseMenu::Close() {
  small_exit_window_->close();
  close();
}

void PauseMenu::SetStyles() {
  setMinimumSize(menu_sizes::kPauseMenuSize);
  for (auto& widget : children()) {
    auto* button_ptr = qobject_cast<QPushButton*>(widget);
    if (button_ptr) {
      button_ptr->setFont(fonts::kDefaultButtonFont);
      button_ptr->setMinimumSize(button_sizes::kPauseMenuMinButtonSize);
      button_ptr->setStyleSheet("QPushButton {"
                                "background-color: #ff9900;"
                                "border-style: outset;"
                                "border-width: 2px;"
                                "border-radius: 10px;"
                                "border-color: beige;"
                                "font: bold 20px; }"

                                "QPushButton::pressed {"
                                "background-color: #e68a00;"
                                "border-style: inset; }");
    }
  }
}

void PauseMenu::SetUpLayout() {
  main_layout_->addStretch(10);
  main_layout_->addWidget(settings_button_, 2, Qt::AlignCenter);
  main_layout_->addWidget(continue_button_, 2, Qt::AlignCenter);
  main_layout_->addWidget(exit_button_, 2, Qt::AlignCenter);
  main_layout_->addStretch(10);
}

void PauseMenu::ConnectUI() {
  connect(exit_button_,
          &QPushButton::clicked,
          small_exit_window_,
          &QWidget::show);
  connect(continue_button_,
          &QPushButton::clicked,
          this,
          &PauseMenu::ContinueGame);
  connect(settings_button_,
          &QPushButton::clicked,
          this,
          &PauseMenu::ShowSettingsFromPM);
  connect(small_exit_window_,
          &SmallExitWindow::ReturnToMainMenu,
          this,
          &PauseMenu::ReturnToMainMenu);
  connect(small_exit_window_,
          &SmallExitWindow::StayAtPauseMenu,
          small_exit_window_,
          &QWidget::close);
}
