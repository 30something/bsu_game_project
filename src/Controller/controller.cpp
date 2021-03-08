
#include "controller.h"

Controller::Controller(QWidget* parent) :
    QWidget(parent),
    model_(new Model()),
    view_(new View(model_)) {
  startTimer(kMillisPerFrame);
}

void Controller::timerEvent(QTimerEvent*) {
  model_->Tick(kMillisPerFrame);

  repaint();
}

void Controller::paintEvent(QPaintEvent*) {
  QPainter main_painter(this);
  view_->Repaint(&main_painter);
}

void Controller::HandleKeyPressEvent(QKeyEvent* event) {
  model_->HandleKeyPressEvent(event);
}

void Controller::HandleKeyReleaseEvent(QKeyEvent* event) {
  model_->HandleKeyReleaseEvent(event);
}
