#include "EventsController.h"

EventsController::EventsController(QWidget* parent) :
    QWidget(parent),
    game_controller_(new GameController()),
    view_(new View(game_controller_)),
    pause_menu_(new PauseMenu(this)) {
  PreparePauseMenu();
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

void EventsController::PreparePauseMenu() {
  pause_menu_->move(width() / 4, height() / 4);
  pause_menu_->close();
  connect(pause_menu_->GetContinueButton(),
          &QPushButton::clicked,
          this,
          &EventsController::SetUnsetPause);
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

const QPushButton* EventsController::GetReturnToMainMenuButton() const {
  return pause_menu_->GetReturnToMainMenuButton();
}

void EventsController::resizeEvent(QResizeEvent*) {
  pause_menu_->setGeometry(0, 0, width(), height());
}
