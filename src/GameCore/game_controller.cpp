#include "game_controller.h"

GameController::GameController(GameMode* game_mode,
                               InputController* input_controller) :
    QObject(nullptr),
    map_(game_mode),
    finish_line_(map_.GetFinishLine()),
    game_mode_(game_mode),
    weapon_handler_(),
    network_controller_(game_mode->network_controller) {
  cars_.reserve(game_mode_->bots_amount
                    + game_mode->network_players_amount
                    + game_mode_->players_amount);
  if (network_controller_) {
    network_controller_->SendStartSignal(JsonHelper::EncodeGameModeJson(
        game_mode->map_index,
        game_mode->bots_amount,
        game_mode->laps_amount,
        game_mode->enable_drifting));
    SetUpCarsNetwork(input_controller);
  } else {
    SetUpCars(input_controller);
  }
  SetUpBots();
  SetUpCarsAchievements();
  weapons_timer_.setSingleShot(true);
  weapons_timer_.start(kMillisWeaponsEnable);
  connect(&weapons_timer_,
          &QTimer::timeout,
          this,
          &GameController::EnableWeapons);
  game_objects_.push_back(
      new WrapperTemplate<GameObject, Mine>(weapon_handler_.GetMines()));
  game_objects_.push_back(
      new WrapperTemplate<GameObject, Bonus>(map_.GetActiveBonuses()));
  game_objects_.push_back(
      new WrapperTemplate<GameObject, Car>(cars_));
}

void GameController::AddCar(Vec2f position,
                            double angle,
                            Behavior* behavior,
                            CarsColors car_color) {
  cars_.emplace_back(position,
                     angle,
                     behavior,
                     car_color,
                     game_mode_->enable_drifting);
}

void GameController::SetUpBots() {
  std::set<CarsColors> colors_set = SetBotsColors();
  for (size_t i = 0; i < game_mode_->bots_amount; i++) {
    size_t id =
        game_mode_->players_amount + game_mode_->network_players_amount + i;
    AddCar(map_.GetPosAndAngles()[id].first,
           map_.GetPosAndAngles()[id].second,
           new BotBehavior(map_.GetBorders(),
                           cars_,
                           map_.GetWaypoints(),
                           map_.GetNoGoLines(),
                           car_achievements_,
                           id,
                           game_mode_),
           static_cast<CarsColors>(*colors_set.begin()));
    colors_set.erase(colors_set.begin());
  }
}

std::set<CarsColors> GameController::SetBotsColors() const {
  std::set<CarsColors> colors_set;
  for (size_t i = 0; i < game_mode_->players_amount +
      game_mode_->network_players_amount + game_mode_->bots_amount; i++) {
    colors_set.insert(static_cast<CarsColors>(i));
  }
  colors_set.erase(static_cast<CarsColors>(
                       game_mode_->first_player_car_number));
  if (game_mode_->players_amount > 1) {
    colors_set.erase(static_cast<CarsColors>(
                         game_mode_->second_player_car_number));
  }
  return colors_set;
}

void GameController::SetUpCarsNetwork(const InputController* input_controller) {
  size_t player_position = network_controller_->GetId();
  for (size_t i = 0; i < player_position; i++) {
    AddCar(map_.GetPosAndAngles()[i].first,
           map_.GetPosAndAngles()[i].second,
           new NetworkPlayerBehavior(network_controller_, i),
           static_cast<CarsColors>(i));
  }
  Behavior* first_player_behavior =
      new FirstPlayerBehavior(input_controller);
  AddCar(map_.GetPosAndAngles()[player_position].first,
         map_.GetPosAndAngles()[player_position].second,
         first_player_behavior,
         static_cast<CarsColors>(player_position));
  new ClientCarDataSender(&cars_.back(),
                          network_controller_,
                          first_player_behavior);
  for (size_t i = player_position + 1;
       i < game_mode_->network_players_amount + 1; i++) {
    AddCar(map_.GetPosAndAngles()[i].first,
           map_.GetPosAndAngles()[i].second,
           new NetworkPlayerBehavior(network_controller_, i),
           static_cast<CarsColors>(i));
  }
}

void GameController::SetUpCars(const InputController* input_controller) {
  AddCar(map_.GetPosAndAngles()[0].first,
         map_.GetPosAndAngles()[0].second,
         new FirstPlayerBehavior(input_controller),
         static_cast<CarsColors>(game_mode_->first_player_car_number));
  if (game_mode_->players_amount > 1) {
    AddCar(map_.GetPosAndAngles()[1].first,
           map_.GetPosAndAngles()[1].second,
           new SecondPlayerBehavior(input_controller),
           static_cast<CarsColors>(game_mode_->second_player_car_number));
  }
}

void GameController::SetUpCarsAchievements() {
  car_achievements_.resize(cars_.size());
  for (uint32_t i = 0; i < cars_.size(); i++) {
    remaining_cars_.insert(i);
    if (i < game_mode_->players_amount) {
      remaining_players_.insert(i);
    }
    car_achievements_[i].car_number = i;
    car_achievements_[i].launched_finish_deviation =
        physics::CalculateLineDeviation(cars_[i].GetPosition().GetX(),
                                        cars_[i].GetPosition().GetY(),
                                        finish_line_);
  }
}

void GameController::Tick(int time_millis) {
  weapon_handler_.ProceedWeapons(&cars_);
  ProceedCollisionsWithCars();
  ProceedCollisionsWithFinish();
  ProceedFinishGame();
  RecalculateDeviations();
  UpdateCarsInfoAndCollisions(time_millis);
}

void GameController::UpdateCarsInfoAndCollisions(int time_millis) {
  for (uint32_t i = 0; i < cars_.size(); i++) {
    map_.HandleCarTick(&cars_[i]);
    cars_[i].Tick(time_millis);
    UpdateCarAchievements(i, cars_[i]);
    if (cars_[i].GetHitPoints() < physics::kAlmostZero) {
      cars_[i].BecomeDead();
      remaining_cars_.erase(i);
      remaining_players_.erase(i);
    }
  }
}

void GameController::UpdateCarAchievements(uint32_t index, const Car& car) {
  car_achievements_[index].hit_points_ = car.GetHitPoints();
  car_achievements_[index].bullets_amount_ = car.GetBulletsAmount();
  car_achievements_[index].mines_amount_ = car.GetMinesAmount();
  if (!car_achievements_[index].is_finished
      && remaining_cars_.find(index) != remaining_cars_.end()) {
    car_achievements_[index].elapsed_millis_time += kMillisPerCarTimeUpdate;
  }
  car_achievements_[index].current_showed_velocity =
      cars_[index].GetVelocity().GetLength();
}

void GameController::RecalculateDeviations() {
  for (uint32_t i = 0; i < cars_.size(); i++) {
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
      auto lines1 = cars_[i].GetCollisionLines();
      auto lines2 = cars_[j].GetCollisionLines();
      if (physics::IsIntersects(lines1, lines2)) {
        CollideCars(&cars_[i], &cars_[j]);
        return;
      }
    }
  }
}

void GameController::ProceedCollisionsWithFinish() {
  for (auto i : remaining_cars_) {
    if (physics::IsIntersects(
        cars_[i].GetCollisionLines(), {finish_line_})) {
      car_achievements_[i].is_collide_with_finish = true;
    } else {
      if (car_achievements_[i].is_collide_with_finish) {
        double start_deviation =
            car_achievements_[i].launched_finish_deviation;
        double past_deviation =
            car_achievements_[i].finish_deviation;
        double current_deviation =
            physics::CalculateLineDeviation(cars_[i].GetPosition().GetX(),
                                            cars_[i].GetPosition().GetY(),
                                            finish_line_);
        if (past_deviation < 0 && current_deviation > 0) {
          if (start_deviation > 0) {
            car_achievements_[i].laps_counter--;
          } else {
            car_achievements_[i].laps_counter++;
          }
        } else if (past_deviation > 0 && current_deviation < 0) {
          if (start_deviation < 0) {
            car_achievements_[i].laps_counter--;
          } else {
            car_achievements_[i].laps_counter++;
          }
        }
      }
      car_achievements_[i].is_collide_with_finish = false;
    }
  }
}

void GameController::ProceedFinishGame() {
  std::vector<uint32_t> deleted_cars;
  for (auto i : remaining_cars_) {
    if (car_achievements_[i].laps_counter > game_mode_->laps_amount) {
      car_achievements_[i].finish_position = next_position_to_finish_++;
      car_achievements_[i].is_finished = true;
      cars_[i].EnableInput(false);
      deleted_cars.push_back(i);
    }
  }
  for (auto i : deleted_cars) {
    remaining_cars_.erase(i);
    remaining_players_.erase(i);
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
  if (network_controller_) {
    result.push_back(cars_[network_controller_->GetId()].GetPosition());
  } else {
    for (size_t i = 0; i < game_mode_->players_amount; i++) {
      result.push_back(cars_[i].GetPosition());
    }
  }
  return result;
}

bool GameController::IsGameFinished() const {
  return remaining_players_.empty();
}

std::vector<CarAchievements> GameController::GetCarsData() const {
  return car_achievements_;
}

void GameController::EnableWeapons() {
  weapon_handler_.SetEnableWeapons(true);
}
