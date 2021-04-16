#include "events_controller.h"

EventsController::EventsController(QWidget* parent, GameMode* game_mode) :
    QWidget(parent),
    game_controller_(new GameController(game_mode)),
    view_(new View(this, game_controller_, game_mode)),
    end_game_stats_(new EndGameStats(this)) {
  PrepareStartCountdownTimer();
  PrepareEndGameStats();
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

void EventsController::resizeEvent(QResizeEvent*) {
  end_game_stats_->setGeometry(0, 0, width(), height());
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

void EventsController::PrepareStartCountdownTimer() {
  connect(&start_countdown_timer_,
          &QTimer::timeout,
          this,
          &EventsController::CheckStartCountdownTimer);
  start_countdown_timer_.start(kMillisInSecond);
}

void EventsController::PrepareEndGameStats() {
  connect(end_game_stats_,
          &EndGameStats::ReturnToMainMenu,
          this,
          &EventsController::ReturnToMainMenu);
  end_game_stats_->close();
}

void EventsController::PrepareGameTimers() {
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
          &EventsController::CheckFinish);
  connect(&finish_pause_timer_,
          &QTimer::timeout,
          end_game_stats_,
          &EndGameStats::show);
  controller_timer_.start(kMillisPerPhysicsTick);
  view_timer_.start(kMillisPerFrame);
  end_game_check_timer_.start(kMillisPerFrame);
}

void EventsController::CheckStartCountdownTimer() {
  if (game_status_ == GameStatus::kPaused) {
    return;
  }
  if (seconds_before_start_ == 0) {
    start_countdown_timer_.stop();
    view_->ClearStartLabel();
    PrepareGameTimers();
  } else {
    view_->UpdateStartLabel(--seconds_before_start_);
  }
}

void EventsController::CheckFinish() {
  if (game_controller_->AllCarsFinished()) {
    end_game_check_timer_.stop();
    finish_pause_timer_.start(kMillisInSecond);
  }
}
