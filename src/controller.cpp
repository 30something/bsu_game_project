#include "controller.h"

Controller::Controller(QWidget* parent) :
    QWidget(parent),
    view_(new View()),
    model_(new Model()) {
  startTimer(kMillisPerFrame);
}

void Controller::timerEvent(QTimerEvent* event) {
  Q_UNUSED(event)
  model_->Tick(kMillisPerFrame);
  repaint();
}

void Controller::paintEvent(QPaintEvent* event) {
  Q_UNUSED(event)
  auto* main_painter = new QPainter();
  view_->Repaint(main_painter);
}

void Controller::keyPressEvent(QKeyEvent* event) {
  model_->KeyPressEvent(event);
}

void Controller::keyReleaseEvent(QKeyEvent* event) {
  model_->KeyReleaseEvent(event);
}
