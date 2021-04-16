#include "game_controller.h"

GameController::GameController(GameMode* game_mode) :
    game_mode_(game_mode),
    weapon_handler_() {
  for (uint32_t i = 0; i < game_mode_->players_amount; i++) {
    remaining_cars_.insert(i);
  }
  car_achievements_.resize(game_mode_->players_amount);
  JsonMapParser parser(map_data::json_filepaths[game_mode->map_index]);
  map_.SetBorders(parser.GetBorders());
  finish_line_ = parser.GetFinishLine();
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
  ProceedCollisionsWithFinish();
  ProceedFinishGame();
  RecalculateDeviations();
  for (uint32_t index = 0; index < cars_.size(); index++) {
    map_.ProceedCollisions(&cars_[index]);
    cars_[index].Tick(time_millis);
    if (cars_[index].GetHitPoints() < physics::kAlmostZero) {
      cars_[index].SetIsAlive(false);
      remaining_cars_.erase(index);
    }
  }
}

void GameController::RecalculateDeviations() {
  for (uint32_t i = 0; i < game_mode_->players_amount; i++) {
    if (!car_achievements_[i].is_collide_with_finish) {
      car_achievements_[i].finish_deviation =
          physics::CalculateLineDeviation(cars_[i].GetPosition().GetX(),
                                          cars_[i].GetPosition().GetY(),
                                          finish_line_);
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

void GameController::ProceedCollisionsWithFinish() {
  for (auto index : remaining_cars_) {
    if (physics::IsIntersects(cars_[index].GetLines(), {finish_line_})) {
      car_achievements_[index].is_collide_with_finish = true;
    } else {
      if (car_achievements_[index].is_collide_with_finish) {
        double past_deviation = car_achievements_[index].finish_deviation;
        double current_deviation =
            physics::CalculateLineDeviation(cars_[index].GetPosition().GetX(),
                                            cars_[index].GetPosition().GetY(),
                                            finish_line_);
        // Variability - depends on finish line location
        if (past_deviation < 0 && current_deviation > 0) {
          car_achievements_[index].laps_counter--;
        } else if (past_deviation > 0 && current_deviation < 0) {
          car_achievements_[index].laps_counter++;
        }
      }
      car_achievements_[index].is_collide_with_finish = false;
    }
  }
}

void GameController::ProceedFinishGame() {
  std::vector<uint32_t> finished_cars;
  for (auto index : remaining_cars_) {
    if (car_achievements_[index].laps_counter > game_mode_->laps_amount) {
      finished_cars.push_back(index);
    }
  }
  for (auto index : finished_cars) {
    car_achievements_[index].is_finished = true;
    remaining_cars_.erase(index);
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
  if (!car_achievements_[0].is_finished
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
      && !car_achievements_[1].is_finished
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

const std::vector<Bonus>& GameController::GetActiveBonuses() const {
  return map_.GetActiveBonuses();
}

double GameController::GetVelocity(int index) const {
  double current_velocity = cars_[index].GetVelocity().GetLength();
  return current_velocity < kMinVisibleVelocity ? 0 : current_velocity;
}

int32_t GameController::GetLapsCounter(int index) const {
  return car_achievements_[index].laps_counter;
}

bool GameController::AllCarsFinished() const {
  return remaining_cars_.empty();
}
