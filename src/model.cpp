#include "model.h"

void Model::Tick(int time_millisec) {
  first_car.Tick(time_millisec);
}
void Model::KeyPressEvent(QKeyEvent* event) {
  int key = event->key();
  if(key == Qt::Key_Up) {
    first_car.SetFlagUp(true);
  }
  if(key == Qt::Key_Down) {
    first_car.SetFlagDown(true);
  }
  if(key == Qt::Key_Left) {
    first_car.SetFlagLeft(true);
  }
  if(key == Qt::Key_Right) {
    first_car.SetFlagRight(true);
  }
}
void Model::KeyReleaseEvent(QKeyEvent* event) {
  int key = event->key();
  if(key == Qt::Key_Up) {
    first_car.SetFlagUp(false);
  }
  if(key == Qt::Key_Down) {
    first_car.SetFlagDown(false);
  }
  if(key == Qt::Key_Left) {
    first_car.SetFlagLeft(false);
  }
  if(key == Qt::Key_Right) {
    first_car.SetFlagRight(false);
  }
}
