#include <iostream>

#include "GameController.h"

GameController::GameController() :
    map_(new Map())
    {
  cars_.emplace_back(car1_start_pos_.x(), car1_start_pos_.y(), car1_start_angle_, map_);
  cars_.emplace_back(car2_start_pos_.x(), car2_start_pos_.y(), car2_start_angle_, map_);
  map_->ParseMapBorders();
}

void GameController::Tick(int time_millisec) {
  for(size_t i = 0; i < cars_.size(); i++) {
    for(size_t j = 0; j < cars_.size() / 2; j++) {
      if(i == j) {
        continue;
      }
      auto lines1 = cars_[i].GetLines();
      auto lines2 = cars_[j].GetLines();
      bool intersects = false;
      for(const auto& line1 : lines1) {
        for(const auto& line2 : lines2) {
          if(Line::IsIntersects(line1, line2)) {
            intersects = true;
          }
        }
      }
      cars_[i].SetIsColliding(intersects);
      cars_[j].SetIsColliding(intersects);
    }
  }
  for(auto& car : cars_) {
    car.Tick(time_millisec);
  }
}

void GameController::HandleKeyPressEvent(QKeyEvent* event) {
  int key = event->key();
  if (key == Qt::Key_Up) {
    cars_[0].SetFlagUp(true);
  }
  if (key == Qt::Key_Down) {
    cars_[0].SetFlagDown(true);
  }
  if (key == Qt::Key_Left) {
    cars_[0].SetFlagLeft(true);
  }
  if (key == Qt::Key_Right) {
    cars_[0].SetFlagRight(true);
  }
  if (key == Qt::Key_W) {
    cars_[1].SetFlagUp(true);
  }
  if (key == Qt::Key_S) {
    cars_[1].SetFlagDown(true);
  }
  if (key == Qt::Key_A) {
    cars_[1].SetFlagLeft(true);
  }
  if (key == Qt::Key_D) {
    cars_[1].SetFlagRight(true);
  }
}

void GameController::HandleKeyReleaseEvent(QKeyEvent* event) {
  int key = event->key();
  if (key == Qt::Key_Up) {
    cars_[0].SetFlagUp(false);
  }
  if (key == Qt::Key_Down) {
    cars_[0].SetFlagDown(false);
  }
  if (key == Qt::Key_Left) {
    cars_[0].SetFlagLeft(false);
  }
  if (key == Qt::Key_Right) {
    cars_[0].SetFlagRight(false);
  }
  if (key == Qt::Key_W) {
    cars_[1].SetFlagUp(false);
  }
  if (key == Qt::Key_S) {
    cars_[1].SetFlagDown(false);
  }
  if (key == Qt::Key_A) {
    cars_[1].SetFlagLeft(false);
  }
  if (key == Qt::Key_D) {
    cars_[1].SetFlagRight(false);
  }
}

std::vector<std::pair<int, int>> GameController::GetCarCoordinates() const {
  std::vector<std::pair<int, int>> result;
  for(const auto& car : cars_) {
    result.emplace_back(car.GetX(), car.GetY());
  }
  return result;
}

std::vector<double> GameController::GetCarAngles() const {
  std::vector<double> result;
  for(const auto& car : cars_) {
    result.push_back(car.GetAngle());
  }
  return result;
}
