#include "pause_menu.h"
#include "src/helpers/sizes.h"

PauseMenu::PauseMenu(QWidget* parent)
    : QWidget(parent),
      main_layout_(new QVBoxLayout(this)),
      settings_button_(new QPushButton("SETTINGS", this)),
      exit_button_(new QPushButton("MAIN MENU", this)),
      continue_button_(new QPushButton("CONTINUE", this)),
      small_exit_window_(new SmallExitWindow(this)) {
  resize(menu_sizes::kPauseMenuSize);
  setStyleSheet("background-color : red");
  settings_button_->setMinimumSize(menu_sizes::kPauseMenuMinButtonSize);
  continue_button_->setMinimumSize(menu_sizes::kPauseMenuMinButtonSize);
  exit_button_->setMinimumSize(menu_sizes::kPauseMenuMinButtonSize);
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
  connect(continue_button_, &QPushButton::clicked, this,
          &PauseMenu::ContinueGame);
  connect(small_exit_window_, &SmallExitWindow::ReturnToMainMenu, this,
          &PauseMenu::ReturnToMainMenu);
  connect(small_exit_window_, &SmallExitWindow::StayAtPauseMenu,
          small_exit_window_, &QWidget::close);
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
