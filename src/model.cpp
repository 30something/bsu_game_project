#include "model.h"

void Model::Tick(int time_millisec) {
  first_car_.Tick(time_millisec);
}
void Model::KeyPressEvent(QKeyEvent* event) {
  int key = event->key();
  if (key == Qt::Key_Up) {
    first_car_.SetFlagUp(true);
  }
  if (key == Qt::Key_Down) {
    first_car_.SetFlagDown(true);
  }
  if (key == Qt::Key_Left) {
    first_car_.SetFlagLeft(true);
  }
  if (key == Qt::Key_Right) {
    first_car_.SetFlagRight(true);
  }
}
void Model::KeyReleaseEvent(QKeyEvent* event) {
  int key = event->key();
  if (key == Qt::Key_Up) {
    first_car_.SetFlagUp(false);
  }
  if (key == Qt::Key_Down) {
    first_car_.SetFlagDown(false);
  }
  if (key == Qt::Key_Left) {
    first_car_.SetFlagLeft(false);
  }
  if (key == Qt::Key_Right) {
    first_car_.SetFlagRight(false);
  }
}

std::pair<int, int> Model::GetCarCoordinates() {
  return std::make_pair(first_car_.GetX(), first_car_.GetY());
}

double Model::GetCarAngle() {
  return first_car_.GetAngle();
}
