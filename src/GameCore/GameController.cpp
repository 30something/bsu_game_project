#include "GameController.h"
#include <iostream>

GameController::GameController(GameMode* game_mode) :
    map_(Map(game_mode)),
    game_mode_(game_mode),
    finish_line_(map_.GetFinishLine()) {
  laps_counters_.resize(game_mode_->players_amount, 0);
  finish_deviations_.resize(game_mode_->players_amount, 0);
  finish_collision_statuses_.resize(
      game_mode_->players_amount, FinishCollisionStatus::kNotCollide);
  cars_.emplace_back(car1_start_pos_.x(),
                     car1_start_pos_.y(),
                     car1_start_angle_);
  for (size_t i = 1; i < game_mode_->players_amount; i++) {
    cars_.emplace_back(car2_start_pos_.x(),
                       car2_start_pos_.y(),
                       car2_start_angle_);
  }
}

void GameController::Tick(int time_millis) {
  ProceedCollisionsWithCars();
  ProceedCollisionsWithFinish();
  for (size_t i = 0; i < game_mode_->players_amount; i++) {
    if (finish_collision_statuses_[i] == FinishCollisionStatus::kNotCollide) {
      finish_deviations_[i] = CalculateFinishDeviation(i);
    }
  }
  for (auto& car : cars_) {
    map_.ProceedCollisions(&car);
    car.Tick(time_millis);
  }
}

void GameController::ProceedCollisionsWithCars() {
  for (size_t i = 0; i < cars_.size(); i++) {
    for (size_t j = 0; j < cars_.size(); j++) {
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

void GameController::ProceedCollisionsWithFinish() {
  for (size_t i = 0; i < cars_.size(); i++) {
    bool collision_exists = false;
    for (const auto& line : cars_[i].GetLines()) {
      if (Line::IsIntersects(line, finish_line_)) {
        collision_exists = true;
        break;
      }
    }
    if (collision_exists) {
      finish_collision_statuses_[i] = FinishCollisionStatus::kCollide;
    } else {
      if (finish_collision_statuses_[i] == FinishCollisionStatus::kCollide) {
        double past_deviation = finish_deviations_[i];
        double current_deviation = CalculateFinishDeviation(i);
        // Variability - depends on finish line location
        if (past_deviation < 0 && current_deviation > 0) {
          laps_counters_[i]--;
        } else if (past_deviation > 0 && current_deviation < 0) {
          laps_counters_[i]++;
        }
      }
      finish_collision_statuses_[i] = FinishCollisionStatus::kNotCollide;
    }
  }
}

double GameController::CalculateFinishDeviation(size_t index) {
  // Using general form of line equation
  double xc = cars_[index].GetPosition().GetX();
  double yc = cars_[index].GetPosition().GetY();
  double A = finish_line_.y1 - finish_line_.y2;
  double B = finish_line_.x2 - finish_line_.x1;
  double C = finish_line_.x1 * finish_line_.y2 -
      finish_line_.x2 * finish_line_.y1;
  double d = (A * xc + B * yc + C) / sqrt(A * A + B * B);
  if (C > 0) {
    d *= -1;
  }
  return d;
}

void GameController::CollideCars(Car* car_1, Car* car_2) {
  Vec2f pos_1 = car_1->GetPosition();
  Vec2f pos_2 = car_2->GetPosition();
  Vec2f deviation
      (pos_1.GetX() - pos_2.GetX(), pos_1.GetY() - pos_2.GetY());
  deviation.Normalize();
  Vec2f vel_1 =
      car_1->GetVelocity() + deviation * physics::kCollisionDeviationScalar;
  Vec2f vel_2 =
      car_2->GetVelocity() - deviation * physics::kCollisionDeviationScalar;
  vel_1 *= kVelocityDecrease;
  vel_2 *= kVelocityDecrease;

  car_1->SetVelocity(vel_1);
  car_2->SetVelocity(vel_2);

  deviation *= kDeviationDecrease;

  car_1->SetPosition(pos_1 + deviation);
  car_2->SetPosition(pos_2 - deviation);
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
  if (game_mode_->players_amount > 1) {
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
  if (game_mode_->players_amount > 1) {
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

int GameController::GetLapsCounter(int index) const {
  return laps_counters_[index];
}

double GameController::GetVelocity(int index) const {
  double current_velocity = cars_[index].GetVelocity().GetLength();
  return current_velocity < kMinVisibleVelocity ? 0 : current_velocity;
}
