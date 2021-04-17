#include "EventsController.h"

EventsController::EventsController(QWidget* parent, GameMode* game_mode) :
    QWidget(parent),
    input_controller_(),
  game_controller_(new GameController(game_mode, &input_controller_)),
  view_(new View(game_mode)) {
  PrepareTimer();
}

void EventsController::PhysicsTimerEvent() {
  if (game_status_ == GameStatus::kRunning) {
    game_controller_->Tick(kMillisPerPhysicsTick);
  }
}

void EventsController::ViewTimerEvent() {
  if (game_status_ == GameStatus::kRunning) {
    repaint();
  }
}

void EventsController::paintEvent(QPaintEvent*) {
  QPainter main_painter(this);
  view_->Repaint(game_controller_->GetGameObjects(),
                 game_controller_->GetPlayersCarPositions(),
                 &main_painter);
}

void EventsController::keyPressEvent(QKeyEvent* event) {
  input_controller_.HandleKeyPressEvent(event);
  if (event->key() == static_cast<int>(Actions::kOpenOrCloseMenu)) {
    SetUnsetPause();
  }
}

void EventsController::keyReleaseEvent(QKeyEvent* event) {
  input_controller_.HandleKeyReleaseEvent(event);
}

void EventsController::SetUnsetPause() {
  if (game_status_ == GameStatus::kRunning) {
    emit SetGamePause();
    game_status_ = GameStatus::kPaused;
    focusNextChild();
  } else {
    emit StopGamePause();
    game_status_ = GameStatus::kRunning;
    setFocus();
  }
}

void EventsController::PrepareTimer() {
  connect(&controller_timer_,
          &QTimer::timeout,
          this,
          &EventsController::PhysicsTimerEvent);
  connect(&view_timer_,
          &QTimer::timeout,
          this,
          &EventsController::ViewTimerEvent);
  controller_timer_.start(kMillisPerPhysicsTick);
  view_timer_.start(kMillisPerFrame);
}
