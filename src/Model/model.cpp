#include "model.h"

void Model::Tick(int time_millisec) {
  car_.Tick(time_millisec);
}

void Model::HandleKeyPressEvent(QKeyEvent* event) {
  int key = event->key();
  if (key == Qt::Key_Up) {
    car_.SetFlagUp(true);
  }
  if (key == Qt::Key_Down) {
    car_.SetFlagDown(true);
  }
  if (key == Qt::Key_Left) {
    car_.SetFlagLeft(true);
  }
  if (key == Qt::Key_Right) {
    car_.SetFlagRight(true);
  }
}

void Model::HandleKeyReleaseEvent(QKeyEvent* event) {
  int key = event->key();
  if (key == Qt::Key_Up) {
    car_.SetFlagUp(false);
  }
  if (key == Qt::Key_Down) {
    car_.SetFlagDown(false);
  }
  if (key == Qt::Key_Left) {
    car_.SetFlagLeft(false);
  }
  if (key == Qt::Key_Right) {
    car_.SetFlagRight(false);
  }
}

std::pair<int, int> Model::GetCarCoordinates() const {
  return std::make_pair(car_.GetX(), car_.GetY());
}

double Model::GetCarAngle() const {
  return car_.GetAngle();
}
