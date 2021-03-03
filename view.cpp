#include "view.h"
#include <QPainter>
#include <QTime>
#include <iostream>

View::View(QWidget* parent) : QWidget(parent) {
  setStyleSheet("background-color:black;");
  resize(800, 800);
  car_.load("car.jpg");
  map_.load("paris.jpg");
  car_ = car_.transformed(QTransform(1, 0, 0, 1, 400, 400));
  timerId_ = startTimer(20);
}

void View::paintEvent(QPaintEvent* e) {
  Q_UNUSED(e);
  QPainter qp(this);
  qp.scale(3, 3);
  qp.drawImage(0, 0, map_, x_, y_, 800, 800);
  qp.translate(400. / 3, 400. / 3);
  qp.rotate(-velocity_.GetAngle());
  qp.drawImage(-5, -5, car_);
}

void View::timerEvent(QTimerEvent*) {
  if (flag_left_) {
    velocity_.RotateCCW(5);
  }
  if (flag_right_) {
    velocity_.RotateCCW(-5);
  }
  if (flag_down_) {
    if (velocity_.GetLength() > max_speed_backward_) {
      velocity_.SetLength(velocity_.GetLength() - 0.5);
    }
  }
  if (flag_up_) {
    if (velocity_.GetLength() < max_speed_forward_) {
      velocity_.SetLength(velocity_.GetLength() + 0.5);
    }
  }
  if (!flag_up_ && velocity_.GetLength() > 0) {
    velocity_.SetLength(velocity_.GetLength() - 0.2);
  }
  if (!flag_down_ && velocity_.GetLength() < 0) {
    velocity_.SetLength(velocity_.GetLength() + 0.2);
  }
  x_ += (velocity_.GetX());
  y_ += (velocity_.GetY());
  repaint();
}

void View::keyPressEvent(QKeyEvent* e) {
  int key = e->key();
  if (key == Qt::Key_Left) {
    flag_left_ = true;
  }
  if (key == Qt::Key_Right) {
    flag_right_ = true;
  }
  if (key == Qt::Key_Down) {
    flag_down_ = true;
  }
  if (key == Qt::Key_Up) {
    flag_up_ = true;
  }
}

void View::keyReleaseEvent(QKeyEvent* e) {
  int key = e->key();
  if (key == Qt::Key_Left) {
    flag_left_ = false;
  }
  if (key == Qt::Key_Right) {
    flag_right_ = false;
  }
  if (key == Qt::Key_Up) {
    flag_up_ = false;
  }
  if (key == Qt::Key_Down) {
    flag_down_ = false;
  }
}

