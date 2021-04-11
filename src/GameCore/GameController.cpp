#include "GameController.h"

GameController::GameController(GameMode* game_mode) :
    game_mode_(game_mode),
    weapon_handler_() {
  for (uint32_t i = 0; i < game_mode_->players_amount; i++) {
    remaining_cars_.insert(i);
  }
  laps_counters_.resize(game_mode_->players_amount, 0);
  finish_deviations_.resize(game_mode_->players_amount, 0);
  finish_collision_statuses_.resize(
      game_mode_->players_amount, FinishCollisionStatus::kNotCollide);
  finish_statuses_.resize(
      game_mode_->players_amount, FinishStatus::kNotFinished);
  JsonMapParser parser(map_data::json_filepaths[game_mode->map_index]);
  map_ = Map(parser.GetBorders());
  finish_line_ = parser.GetFinishLine();
  std::vector<std::pair<QPoint, double>>
      pos_and_angles = parser.GetCarStartPositionsAndAngles();
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
  ProceedCollisionsWithFinish();
  ProceedFinishGame();
  RecalculateDeviations();
  for (uint32_t index = 0; index < cars_.size(); index++) {
    map_.ProceedCollisions(&cars_[index]);
    cars_[index].Tick(time_millis);
    if (cars_[index].GetHitPoints() < Physics::kAlmostZero) {
      cars_[index].SetIsAlive(false);
      remaining_cars_.erase(index);
    }
  }
}

void GameController::RecalculateDeviations() {
  for (size_t i = 0; i < game_mode_->players_amount; i++) {
    if (finish_collision_statuses_[i] == FinishCollisionStatus::kNotCollide) {
      finish_deviations_[i] = CalculateFinishDeviation(i);
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
      if (Physics::IsIntersects(lines1, lines2)) {
        CollideCars(&cars_[i], &cars_[j]);
        return;
      }
    }
  }
}

void GameController::ProceedCollisionsWithFinish() {
  for (auto index : remaining_cars_) {
    bool collision_exists = false;
    for (const auto& line : cars_[index].GetLines()) {
      if (Physics::IsIntersects(line, finish_line_)) {
        collision_exists = true;
        break;
      }
    }
    if (collision_exists) {
      finish_collision_statuses_[index] = FinishCollisionStatus::kCollide;
    } else {
      if (finish_collision_statuses_[index]
          == FinishCollisionStatus::kCollide) {
        double past_deviation = finish_deviations_[index];
        double current_deviation = CalculateFinishDeviation(index);
        // Variability - depends on finish line location
        if (past_deviation < 0 && current_deviation > 0) {
          laps_counters_[index]--;
        } else if (past_deviation > 0 && current_deviation < 0) {
          laps_counters_[index]++;
        }
      }
      finish_collision_statuses_[index] = FinishCollisionStatus::kNotCollide;
    }
  }
}

void GameController::ProceedFinishGame() {
  std::vector<uint32_t> finished_cars;
  for (auto index : remaining_cars_) {
    if (laps_counters_[index] > static_cast<int32_t>(game_mode_->laps_amount)) {
      finished_cars.push_back(index);
    }
  }
  for (auto index : finished_cars) {
    finish_statuses_[index] = FinishStatus::kFinished;
    remaining_cars_.erase(index);
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
  double relative_speed =
      (car_1->GetVelocity() - car_2->GetVelocity()).GetLength();
  car_1->AddHitPoints(-relative_speed * kHPDecrease);
  car_2->AddHitPoints(-relative_speed * kHPDecrease);
  Vec2f deviation
      (pos_1.GetX() - pos_2.GetX(), pos_1.GetY() - pos_2.GetY());
  deviation.Normalize();
  Vec2f vel_1 =
      car_1->GetVelocity() + deviation * Physics::kCollisionDeviationScalar;
  Vec2f vel_2 =
      car_2->GetVelocity() - deviation * Physics::kCollisionDeviationScalar;
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
  if (finish_statuses_[0] == FinishStatus::kNotFinished
      && cars_[0].IsAlive()) {
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
  if (game_mode_->players_amount > 1
      && finish_statuses_[1] == FinishStatus::kNotFinished
      && cars_[1].IsAlive()) {
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

double GameController::GetVelocity(int index) const {
  double current_velocity = cars_[index].GetVelocity().GetLength();
  return current_velocity < kMinVisibleVelocity ? 0 : current_velocity;
}

int32_t GameController::GetLapsCounter(int index) const {
  return laps_counters_[index];
}

bool GameController::AllCarsFinished() const {
  return remaining_cars_.empty();
}
