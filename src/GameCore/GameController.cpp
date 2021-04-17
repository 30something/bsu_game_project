#include "GameController.h"

GameController::GameController(GameMode* game_mode,
                               InputController* input_controller) :
    game_mode_(game_mode),
    weapon_handler_() {
  JsonMapParser parser(map_data::json_filepaths[game_mode->map_index]);
  map_.SetBorders(parser.GetBorders());
  std::vector<std::pair<QPoint, double>> pos_and_angles =
      parser.GetCarStartPositionsAndAngles();
  Behavior* first_player_behavior =
      new FirstPlayerBehavior(input_controller);
  cars_.emplace_back(
      pos_and_angles[0].first,
      pos_and_angles[0].second,
      first_player_behavior);
  if (game_mode_->players_amount > 1) {
    Behavior* second_player_behavior =
        new SecondPlayerBehavior(input_controller);
    cars_.emplace_back(
        pos_and_angles[1].first,
        pos_and_angles[1].second,
        second_player_behavior);
  }
  for (size_t i = 0; i < game_mode_->bots_amount; i++) {
    auto* bot = new BotBehavior(parser.GetBorders(),
                                       &cars_,
                                       &map_.GetActiveBonuses(),
                                       &weapon_handler_.GetMines());
    cars_.emplace_back(
                  pos_and_angles[game_mode_->players_amount + i].first,
                  pos_and_angles[game_mode_->players_amount + i].second,
                  bot);
  }
  game_objects_.push_back(
      new WrapperTemplate<GameObject, Car>(cars_));
  game_objects_.push_back(
      new WrapperTemplate<GameObject, Mine>(weapon_handler_.GetMines()));
  game_objects_.push_back(
      new WrapperTemplate<GameObject, Bonus>(map_.GetActiveBonuses()));
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
      auto lines1 = cars_[i].GetCollisionLines();
      auto lines2 = cars_[j].GetCollisionLines();
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

std::vector<WrapperBase<GameObject>*> GameController::GetGameObjects() const {
  return game_objects_;
}

std::vector<Vec2f> GameController::GetPlayersCarPositions() const {
  std::vector<Vec2f> result;
  for (size_t i = 0; i < game_mode_->players_amount; i++) {
    result.push_back(cars_[i].GetPosition());
  }
  return result;
}
