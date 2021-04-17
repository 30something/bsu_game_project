#include "events_controller.h"

EventsController::EventsController(QWidget* parent, GameMode* game_mode) :
    QWidget(parent),
    input_controller_(),
    game_controller_(new GameController(game_mode, &input_controller_)),
    view_(new View(game_mode)),
    view_info_updater_(new ViewInfoUpdater(this,
                                           game_controller_,
                                           view_,
                                           game_mode)),
    end_game_stats_(new EndGameStats(this)) {
  PrepareStartCountdownTimer();
  PrepareEndGameStats();
}

void EventsController::PhysicsTimerEvent() {
  if (game_status_ == GameStatus::kRunning) {
    game_controller_->Tick(kMillisPerPhysicsTick);
    if (game_controller_->AllCarsFinished()
        && finish_status_ == FinishStatus::kNotFinished) {
      finish_status_ = FinishStatus::kFinished;
      PrepareFinishTimer();
    }
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
  view_info_updater_->Repaint(&main_painter);
}

void EventsController::resizeEvent(QResizeEvent*) {
  end_game_stats_->setGeometry(0, 0, width(), height());
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

void EventsController::UpdateStartInfo() {
  if (game_status_ == GameStatus::kRunning) {
    view_info_updater_->UpdateStartInfo();
    if (view_info_updater_->GetStartState()) {
      start_countdown_timer_.stop();
      PrepareGameTimers();
    }
  }
}

void EventsController::ShowEndGameStats() {
  finish_pause_timer_.stop();
  end_game_stats_->show();
}

void EventsController::PrepareStartCountdownTimer() {
  connect(&start_countdown_timer_,
          &QTimer::timeout,
          this,
          &EventsController::UpdateStartInfo);
  start_countdown_timer_.start(kMillisInSecond);
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
  controller_timer_.start(kMillisPerPhysicsTick);
  view_timer_.start(kMillisPerFrame);
}

void EventsController::PrepareEndGameStats() {
  connect(end_game_stats_,
          &EndGameStats::ReturnToMainMenu,
          this,
          &EventsController::ReturnToMainMenu);
  end_game_stats_->close();
}

void EventsController::PrepareFinishTimer() {
  connect(&finish_pause_timer_,
          &QTimer::timeout,
          this,
          &EventsController::ShowEndGameStats);
  finish_pause_timer_.start(kMillisInSecond);
}