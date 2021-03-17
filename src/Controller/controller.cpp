#include "controller.h"

Controller::Controller(QWidget* parent) :
    QWidget(parent),
    model_(new Model()),
    view_(new View(model_)),
    pause_menu_(new PauseMenu(this)) {
  pause_menu_->move(width() / 4, height() / 4);
  pause_menu_->close();
  connect(pause_menu_->GetContinueButton(), &QPushButton::clicked,
          this, &Controller::SetUnsetPause);
  startTimer(kMillisPerFrame);
}

void Controller::timerEvent(QTimerEvent*) {
  if (game_status_ == GameStatus::kRunning) {
    model_->Tick(kMillisPerFrame);
    repaint();
  }
}

void Controller::paintEvent(QPaintEvent*) {
  QPainter main_painter(this);
  view_->Repaint(&main_painter);
}

void Controller::keyPressEvent(QKeyEvent* event) {
  model_->HandleKeyPressEvent(event);
  if (event->key() == static_cast<int>(Actions::kOpenOrCloseMenu)) {
    SetUnsetPause();
  }
}

void Controller::keyReleaseEvent(QKeyEvent* event) {
  model_->HandleKeyReleaseEvent(event);
}

void Controller::SetUnsetPause() {
  if (game_status_ == GameStatus::kRunning) {
    pause_menu_->show();
    game_status_ = GameStatus::kPaused;
    focusNextChild();
  } else {
    pause_menu_->close();
    game_status_ = GameStatus::kRunning;
    setFocus();
  }
}

QPushButton* Controller::GetReturnToMainMenuButton() const {
  return pause_menu_->GetReturnToMainMenuButton();
}

void Controller::resizeEvent(QResizeEvent*) {
  pause_menu_->setGeometry(0, 0, width(), height());
}
