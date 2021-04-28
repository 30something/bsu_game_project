#include "EventsController.h"

EventsController::EventsController(QWidget *parent, GameMode *game_mode) :
        QWidget(parent),
        game_controller_(new GameController(game_mode)),
        view_(new View(this, game_controller_, game_mode)) {
    PrepareTimer();
}

void EventsController::PhysicsTimerEvent() {
    if (game_status_ == GameStatus::kRunning) {
        game_controller_->Tick(kMillisPerPhysicsTick);

        PlaySounds();
    }
}

void EventsController::ViewTimerEvent() {
    if (game_status_ == GameStatus::kRunning) {
        repaint();
    }
}

void EventsController::paintEvent(QPaintEvent *) {
    QPainter main_painter(this);
    view_->Repaint(&main_painter);
}

void EventsController::keyPressEvent(QKeyEvent *event) {
    game_controller_->HandleKeyPressEvent(event);
    if (event->key() == static_cast<int>(Actions::kOpenOrCloseMenu)) {
        SetUnsetPause();
    }
}

void EventsController::keyReleaseEvent(QKeyEvent *event) {
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

void EventsController::PlaySounds() {
    view_->PlayEngine(game_controller_->GetParametersForEngineSound().first,
                      game_controller_->GetParametersForEngineSound().second,
                      game_controller_->FirstCarIsAlive());
    view_->PlayDrift(game_controller_->GetCoefficientForDriftSound());
    view_->PlayBrake(game_controller_->GetCoefficientForBrakeSound());

    view_->PlayBonus(game_controller_->BonusIsApplied());
    view_->PlayShooting(game_controller_->GetParametersForShootingSound().first,
                        game_controller_->GetParametersForShootingSound().second);
    view_->PlayMine(game_controller_->MineIsExploded());
    view_->PlayCarExplosion(game_controller_->CarIsExploded());
}
