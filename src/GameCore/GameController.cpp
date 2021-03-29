#include <iostream>

#include "GameController.h"

GameController::GameController(uint map_index) :
    map_(Map(map_index)) {
  cars_.emplace_back(car1_start_pos_.x(),
                     car1_start_pos_.y(),
                     car1_start_angle_);
  cars_.emplace_back(car2_start_pos_.x(),
                     car2_start_pos_.y(),
                     car2_start_angle_);
}

void GameController::Tick(int time_millis) {
  ProceedColisionsWithCars();
  for (auto& car : cars_) {
    map_.ProceedCollisions(&car);
    car.Tick(time_millis);
  }
}

void GameController::ProceedColisionsWithCars() {
  for (size_t i = 0; i < cars_.size(); i++) {
    for (size_t j = 0; j < cars_.size() / 2; j++) {
      if (i == j) {
        continue;
      }
      auto lines1 = cars_[i].GetLines();
      auto lines2 = cars_[j].GetLines();
      for (const auto& line1 : lines1) {
        for (const auto& line2 : lines2) {
          if (Line::IsIntersects(line1, line2)) {
            CollideCars(&cars_[i], &cars_[j]);
            return;
          }
        }
      }
    }
  }
}

void GameController::CollideCars(Car* car_1, Car* car_2) {
  Vec2f pos_1 = car_1->GetPosition();
  Vec2f pos_2 = car_2->GetPosition();
  Vec2f deviation_1
      (pos_1.GetX() - pos_2.GetX(), pos_1.GetY() - pos_2.GetY());
  deviation_1.Normalize();
  Vec2f vel_1 =
      car_1->GetVelocity() + deviation_1 * physics::kCollisionDeviationScalar;
  Vec2f vel_2 =
      car_2->GetVelocity() - deviation_1 * physics::kCollisionDeviationScalar;
  vel_1 *= 0.5;
  vel_2 *= 0.5;

  car_1->SetVelocity(vel_1);
  car_2->SetVelocity(vel_2);

  car_1->SetPosition(pos_1 + deviation_1);
  car_2->SetPosition(pos_2 - deviation_1);
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

std::vector<QPoint> GameController::GetCarCoordinates() const {
  std::vector<QPoint> result;
  for (const auto& car : cars_) {
    result.emplace_back(car.GetX(), car.GetY());
  }
  return result;
}

std::vector<double> GameController::GetCarAngles() const {
  std::vector<double> result;
  for (const auto& car : cars_) {
    result.push_back(car.GetAngle());
  }
  return result;
}
