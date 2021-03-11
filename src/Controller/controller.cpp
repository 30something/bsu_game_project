#include "controller.h"

Controller::Controller(QWidget* parent) :
    QWidget(parent),
    model_(new Model()),
    view_(new View(model_)),
    pause_menu_(new PauseMenu(this)) {
  pause_menu_->move(width() / 4, height() / 4);
  pause_menu_->close();
  connect(pause_menu_->continue_button_, &QPushButton::clicked,
          this, &Controller::UnsetPause);
  startTimer(kMillisPerFrame);
}

void Controller::timerEvent(QTimerEvent*) {
  if (!is_game_paused_) {
    model_->Tick(kMillisPerFrame);
  }
  repaint();
}

void Controller::paintEvent(QPaintEvent*) {
  QPainter main_painter(this);
  view_->Repaint(&main_painter);
}

void Controller::HandleKeyPressEvent(QKeyEvent* event) {
  model_->HandleKeyPressEvent(event);
  if (event->key() == Qt::Key_Escape) {
    if (!is_game_paused_) {
      SetPause();
    } else {
      UnsetPause();
    }
  }
}

void Controller::HandleKeyReleaseEvent(QKeyEvent* event) {
  model_->HandleKeyReleaseEvent(event);
}

void Controller::SetPause() {
  pause_menu_->show();
  is_game_paused_ = true;
  focusNextChild();
}

void Controller::UnsetPause() {
  pause_menu_->close();
  is_game_paused_ = false;
  setFocus();
}
