#include "controller.h"

Controller::Controller(QWidget* parent) :
    QWidget(parent),
    model_(new Model()),
    view_(new View(model_)),
    pause_menu_(new PauseMenu(this)) {
  PreparePauseMenu();
  PrepareTimer();
}

void Controller::PhysicsTimerEvent() {
  if (game_status_ == GameStatus::kRunning) {
    model_->Tick(kMillisPerPhysicsTick);
  }

}

void Controller::ViewTimerEvent() {
  if (game_status_ == GameStatus::kRunning) {
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
    pause_menu_->CloseSmallExitWindow();
    game_status_ = GameStatus::kRunning;
    setFocus();
  }
}

void Controller::PreparePauseMenu() {
  pause_menu_->move(width() / 4, height() / 4);
  pause_menu_->close();
  connect(pause_menu_->GetContinueButton(),
          &QPushButton::clicked,
          this,
          &Controller::SetUnsetPause);
}

void Controller::PrepareTimer() {
  connect(&controller_timer_,
          &QTimer::timeout,
          this,
          &Controller::PhysicsTimerEvent);
  connect(&view_timer_,
          &QTimer::timeout,
          this,
          &Controller::ViewTimerEvent);
  controller_timer_.start(kMillisPerPhysicsTick);
  view_timer_.start(kMillisPerFrame);
}

const QPushButton* Controller::GetReturnToMainMenuButton() const {

  return pause_menu_->GetReturnToMainMenuButton();
}

void Controller::resizeEvent(QResizeEvent*) {
  pause_menu_->setGeometry(0, 0, width(), height());
}
