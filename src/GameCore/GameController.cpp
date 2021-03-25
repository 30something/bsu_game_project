#include "GameController.h"

GameController::GameController() :
    map_(new Map()),
    car_(car_start_pos_.x(), car_start_pos_.y(), car_start_angle_, map_) {
  map_->ParseMapBorders();
}

void GameController::Tick(int time_millisec) {
  car_.Tick(time_millisec);
}

void GameController::HandleKeyPressEvent(QKeyEvent* event) {
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

void GameController::HandleKeyReleaseEvent(QKeyEvent* event) {
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

std::pair<int, int> GameController::GetCarCoordinates() const {
  return std::make_pair(car_.GetX(), car_.GetY());
}

double GameController::GetCarAngle() const {
  return car_.GetAngle();
}
