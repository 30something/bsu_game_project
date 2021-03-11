#include "controller.h"

Controller::Controller(QWidget *parent) :
    QWidget(parent),
    model_(new Model()),
    view_(new View(model_)),
    stacked_widget_(new QStackedWidget(this)),
    pause_menu_(new PauseMenu(stacked_widget_)) {
  stacked_widget_->resize(pause_menu_->GetWidth(), pause_menu_->GetHeight());
  stacked_widget_->move(width() / 4, height() / 4);
  stacked_widget_->addWidget(pause_menu_);
  stacked_widget_->close();
  connect(pause_menu_->continue_button_, &QPushButton::clicked,
          this, &Controller::UnsetPause);
  startTimer(kMillisPerFrame);
}

void Controller::timerEvent(QTimerEvent *) {
  model_->Tick(kMillisPerFrame);
  repaint();
}

void Controller::paintEvent(QPaintEvent *) {
  QPainter main_painter(this);
  view_->Repaint(&main_painter);
}

void Controller::HandleKeyPressEvent(QKeyEvent *event) {
  model_->HandleKeyPressEvent(event);
  if (event->key() == Qt::Key_Escape) {
    if (!is_game_paused_) {
      SetPause();
    } else {
      UnsetPause();
    }
  }
}

void Controller::HandleKeyReleaseEvent(QKeyEvent *event) {
  model_->HandleKeyReleaseEvent(event);
}

void Controller::SetPause() {
  stacked_widget_->show();
  is_game_paused_ = true;
}

void Controller::UnsetPause() {
  stacked_widget_->close();
  is_game_paused_ = false;
}
