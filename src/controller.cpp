
#include "controller.h"

Controller::Controller(QWidget* parent) :
    QWidget(parent),
    model_(new Model()),
    view_(new View(model_)) {
  startTimer(kMillisPerFrame);
}

void Controller::timerEvent(QTimerEvent* event) {
  Q_UNUSED(event)
  model_->Tick(kMillisPerFrame);

  repaint();
}

void Controller::paintEvent(QPaintEvent* event) {
  Q_UNUSED(event)
  QPainter main_painter(this);
  view_->Repaint(&main_painter);
}

void Controller::KeyPressEvent(QKeyEvent* event) {
  model_->KeyPressEvent(event);
}

void Controller::KeyReleaseEvent(QKeyEvent* event) {
  model_->KeyReleaseEvent(event);
}
