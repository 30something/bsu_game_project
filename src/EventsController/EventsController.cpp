#include "EventsController.h"

EventsController::EventsController(QWidget* parent, int map_index) :
    QWidget(parent),
    game_controller_(new GameController(map_index)),
    view_(new View(game_controller_, map_index)) {
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
  view_->Repaint(&main_painter);
}

void EventsController::keyPressEvent(QKeyEvent* event) {
  game_controller_->HandleKeyPressEvent(event);
  if (event->key() == static_cast<int>(Actions::kOpenOrCloseMenu)) {
    SetUnsetPause();
  }
}

void EventsController::keyReleaseEvent(QKeyEvent* event) {
  game_controller_->HandleKeyReleaseEvent(event);
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
