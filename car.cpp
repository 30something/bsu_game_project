#include "car.h"
#include <QPainter>
#include <QTime>
#include <iostream>

Car::Car(QWidget* parent) : QWidget(parent) {
  setStyleSheet("background-color:black;");
  resize(800, 800);
  car_.load("car.jpg");
  map.load("paris.jpg");
  car_ = car_.transformed(QTransform(1, 0, 0, 1, 400, 400));
  timerId = startTimer(20);
}

void Car::paintEvent(QPaintEvent* e) {
  Q_UNUSED(e);
  QPainter qp(this);
  qp.scale(3, 3);
  qp.drawImage(0, 0, map, x_, y_, 800, 800);
  qp.translate(400. / 3, 400. / 3);
  qp.rotate(-velocity_.GetAngle());
  qp.drawImage(-5, -5, car_);
}

void Car::timerEvent(QTimerEvent*) {
  if (flag_left) {
    velocity_.RotateCCW(5);
  }
  if (flag_right) {
    velocity_.RotateCCW(-5);
  }
  if (flag_down) {
    if (velocity_.GetLength() > max_speed_backward) {
      velocity_.SetLength(velocity_.GetLength() - 0.5);
    }
  }
  if (flag_up) {
    if (velocity_.GetLength() < max_speed_forward) {
      velocity_.SetLength(velocity_.GetLength() + 0.5);
    }
  }
  if (!flag_up && velocity_.GetLength() > 0) {
    velocity_.SetLength(velocity_.GetLength() - 0.2);
  }
  if (!flag_down && velocity_.GetLength() < 0) {
    velocity_.SetLength(velocity_.GetLength() + 0.2);
  }
  x_ += (velocity_.GetX());
  y_ += (velocity_.GetY());
  repaint();
}

void Car::keyPressEvent(QKeyEvent* e) {
  int key = e->key();
  if (key == Qt::Key_Left) {
    flag_left = true;
  }
  if (key == Qt::Key_Right) {
    flag_right = true;
  }
  if (key == Qt::Key_Down) {
    flag_down = true;
  }
  if (key == Qt::Key_Up) {
    flag_up = true;
  }
}

void Car::keyReleaseEvent(QKeyEvent* e) {
  int key = e->key();
  if (key == Qt::Key_Left) {
    flag_left = false;
  }
  if (key == Qt::Key_Right) {
    flag_right = false;
  }
  if (key == Qt::Key_Up) {
    flag_up = false;
  }
  if (key == Qt::Key_Down) {
    flag_down = false;
  }
}

