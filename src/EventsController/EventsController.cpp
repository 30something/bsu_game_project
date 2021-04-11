#include "EventsController.h"

EventsController::EventsController(QWidget* parent, GameMode* game_mode) :
    QWidget(parent),
    game_controller_(new GameController(game_mode)),
    view_(new View(this, game_controller_, game_mode)) {
  connect(&start_timer_,
          &QTimer::timeout,
          this,
          &EventsController::StartTimer);
  start_timer_.start(kMillisInSecond);
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
  connect(&end_game_check_timer_,
          &QTimer::timeout,
          this,
          &EventsController::FinishCheck);
  connect(&finish_pause_,
          &QTimer::timeout,
          this,
          &EventsController::ShowStats);
  controller_timer_.start(kMillisPerPhysicsTick);
  view_timer_.start(kMillisPerFrame);
  end_game_check_timer_.start(kMillisPerFrame);
}

void EventsController::StartTimer() {
  if (game_status_ == GameStatus::kPaused) {
    return;
  }
  if (seconds_before_start_ == 0) {
    start_timer_.stop();
    view_->UpdateStartLabel("");
    PrepareTimer();
  } else {
    seconds_before_start_--;
    if (seconds_before_start_ == 0) {
      view_->UpdateStartLabel("Go!");
    } else {
      view_->UpdateStartLabel(std::to_string(seconds_before_start_));
    }
  }
}

void EventsController::FinishCheck() {
  if (game_controller_->AllCarsFinished()) {
    end_game_check_timer_.stop();
    finish_pause_.start(kMillisInSecond);
  }
}
