#include "GameController.h"

GameController::GameController(GameMode* game_mode) :
    game_mode_(game_mode),
    weapon_handler_() {
  JsonMapParser parser(map_data::json_filepaths[game_mode->map_index]);
  map_.SetBorders(parser.GetBorders());
  std::vector<std::pair<QPoint, double>> pos_and_angles =
      parser.GetCarStartPositionsAndAngles();
  size_t cars_amount = game_mode_->players_amount + game_mode_->bots_amount;
  for (size_t i = 0; i < cars_amount; i++) {
    cars_.emplace_back(
        pos_and_angles[i].first.x(),
        pos_and_angles[i].first.y(),
        pos_and_angles[i].second);
  }
}

void GameController::Tick(int time_millis) {
  weapon_handler_.ProceedWeapons(&cars_);
  ProceedCollisionsWithCars();
  for (auto& car : cars_) {
    map_.HandleCarTick(&car);
    car.Tick(time_millis);
    if (car.GetHitPoints() < physics::kAlmostZero) {
      car.SetIsAlive(false);
    }
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
      if (physics::IsIntersects(lines1, lines2)) {
        CollideCars(&cars_[i], &cars_[j]);
        return;
      }
    }
  }
}

void GameController::CollideCars(Car* car_1, Car* car_2) {
  Vec2f pos_1 = car_1->GetPosition();
  Vec2f pos_2 = car_2->GetPosition();
  double relative_speed =
      (car_1->GetVelocity() - car_2->GetVelocity()).GetLength();
  car_1->AddHitPoints(-relative_speed * kHPDecrease);
  car_2->AddHitPoints(-relative_speed * kHPDecrease);
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
  if (cars_[0].IsAlive()) {
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
    if (key == Qt::Key_Control) {
      cars_[0].SetIsShooting(true);
    }
    if (key == Qt::Key_Shift) {
      weapon_handler_.PutMine(&cars_[0]);
    }
  }
  if (game_mode_->players_amount > 1 && cars_[1].IsAlive()) {
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
    if (key == Qt::Key_Alt) {
      cars_[1].SetIsShooting(true);
    }
    if (key == Qt::Key_Space) {
      weapon_handler_.PutMine(&cars_[1]);
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
  if (key == Qt::Key_Control) {
    cars_[0].SetIsShooting(false);
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
    if (key == Qt::Key_Alt) {
      cars_[1].SetIsShooting(false);
    }
  }
}

const std::vector<QPoint>& GameController::GetMinesCoordinates() const {
  return weapon_handler_.GetMinesCoordinates();
}

const std::vector<Car>& GameController::GetCars() const {
  return cars_;
}

const std::vector<Bonus>& GameController::GetActiveBonuses() const {
  return map_.GetActiveBonuses();
}

std::pair<double, int> GameController::GetParametersForEngineSound() {
    return cars_[0].GetParametersForEngineSound();
}

double GameController::GetCoefficientForDriftSound() {
    return cars_[0].GetCoefficientForDriftSound();
}

double GameController::GetCoefficientForBrakeSound() {
    return cars_[0].GetCoefficientForBrakeSound();
}