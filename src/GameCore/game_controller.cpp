#include "game_controller.h"

GameController::GameController(GameMode* game_mode,
                               InputController* input_controller) :
    QObject(nullptr),
    map_(map_data::json_file_paths.file_paths[game_mode->map_index]),
    finish_line_(map_.GetFinishLine()),
    game_mode_(game_mode),
    weapon_handler_(),
    network_controller_(game_mode->network_controller) {
  if (network_controller_ != nullptr) {
    SetUpCarsNetwork(input_controller);
    data_send_timer_.start(kMillisDataSend);
    connect(&data_send_timer_,
            &QTimer::timeout,
            this,
            &GameController::SendCarData);
  } else {
    SetUpCars(input_controller);
    SetUpBots();
  }
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

void GameController::SetUpBots() {
  for (size_t i = 0; i < game_mode_->bots_amount; i++) {
    auto* bot = new BotBehavior(map_.GetBorders(),
                                cars_,
                                map_.GetWaypoints(),
                                map_.GetNoGoLines(),
                                game_mode_);
    cars_.emplace_back(
        map_.GetPosAndAngles()[game_mode_->players_amount + i].first,
        map_.GetPosAndAngles()[game_mode_->players_amount + i].second,
        bot,
        static_cast<CarsColors>(i + 2),
        game_mode_->enable_drifting);
  }
}

void GameController::SetUpCarsNetwork(const InputController* input_controller) {
  for (size_t i = 0; i < network_controller_->GetId(); i++) {
    auto* network_player_behavior = new NetworkPlayerBehavior(
        network_controller_,
        i);
    cars_.emplace_back(
        map_.GetPosAndAngles()[0].first,
        map_.GetPosAndAngles()[0].second,
        network_player_behavior,
        static_cast<CarsColors>(0),
        game_mode_->enable_drifting
        );
  }
  Behavior* first_player_behavior =
      new FirstPlayerBehavior(input_controller);
  our_car_behavior_ = first_player_behavior;
  cars_.emplace_back(
      map_.GetPosAndAngles()[0].first,
      map_.GetPosAndAngles()[0].second,
      first_player_behavior,
      static_cast<CarsColors>(0),
      game_mode_->enable_drifting);
  for (size_t i = network_controller_->GetId() + 1; i < game_mode_->network_players_amount + 1; i++) {
    auto* network_player_behavior = new NetworkPlayerBehavior(
        network_controller_,
        i);
    cars_.emplace_back(
        map_.GetPosAndAngles()[0].first,
        map_.GetPosAndAngles()[0].second,
        network_player_behavior,
        static_cast<CarsColors>(0),
        game_mode_->enable_drifting
    );
  }
}

void GameController::SetUpCars(const InputController* input_controller) {
  Behavior* first_player_behavior =
      new FirstPlayerBehavior(input_controller);
  cars_.emplace_back(
      map_.GetPosAndAngles()[0].first,
      map_.GetPosAndAngles()[0].second,
      first_player_behavior,
      static_cast<CarsColors>(0),
      game_mode_->enable_drifting);
  if (game_mode_->players_amount > 1) {
    Behavior* second_player_behavior =
        new SecondPlayerBehavior(input_controller);
    cars_.emplace_back(
        map_.GetPosAndAngles()[1].first,
        map_.GetPosAndAngles()[1].second,
        second_player_behavior,
        static_cast<CarsColors>(1),
        game_mode_->enable_drifting);
  }
}

void GameController::SetUpCarsAchievements() {
  car_achievements_.resize(cars_.size());
  for (uint32_t i = 0; i < cars_.size(); i++) {
    remaining_cars_.insert(i);
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
    car_achievements_[i].current_showed_velocity =
        cars_[i].GetVelocity().GetLength();
    if (cars_[i].GetHitPoints() < physics::kAlmostZero) {
      cars_[i].BecomeDead();
      remaining_cars_.erase(i);
    }
  }
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
      cars_[i].EnableInput(false);
      deleted_cars.push_back(i);
    }
  }
  for (auto i : deleted_cars) {
    remaining_cars_.erase(i);
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

bool GameController::AllCarsFinished() const {
  return remaining_cars_.empty();
}

std::vector<CarAchievements> GameController::GetCarsData() const {
  return car_achievements_;
}

void GameController::EnableWeapons() {
  weapon_handler_.SetEnableWeapons(true);
}

void GameController::SendCarData() {
  PlayerCarData data;
  data.angle = cars_[network_controller_->GetId()].GetAngleVec();
  data.position = cars_[network_controller_->GetId()].GetPosition();
  data.flag_up = our_car_behavior_->IsFlagUp();
  data.flag_down = our_car_behavior_->IsFlagDown();
  data.flag_left = our_car_behavior_->IsFlagLeft();
  data.flag_right = our_car_behavior_->IsFlagRight();
  data.flag_shoot = our_car_behavior_->IsFlagShoot();
  data.flag_mine = our_car_behavior_->IsFlagMine();
  network_controller_->SendCarData(data);
}
