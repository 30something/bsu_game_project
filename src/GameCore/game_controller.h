#pragma once

#include <set>
#include <utility>
#include <vector>

#include <QKeyEvent>
#include <QTextStream>
#include <QFile>
#include <QPoint>

#include "src/GameCore/GameObjects/car.h"
#include "game_map.h"
#include "weapon_handler.h"
#include "src/helpers/json_map_parser.h"
#include "src/GameCore/car_achievements.h"
#include "src/GameCore/Behaviors/first_player_behavior.h"
#include "src/GameCore/Behaviors/second_player_behavior.h"
#include "input_controller.h"
#include "src/helpers/wrapper_template.h"

class GameController {
 public:
  explicit GameController(GameMode* game_mode, InputController*);
  ~GameController() = default;

  void Tick(int time_millis);

  std::vector<WrapperBase<GameObject>*> GetGameObjects() const;
  std::vector<Vec2f> GetPlayersCarPositions() const;

  double GetVelocity(int index) const;
  int32_t GetLapsCounter(int index) const;
  bool AllCarsFinished() const;

 private:
  void ProceedCollisionsWithCars();
  void ProceedCollisionsWithFinish();
  void ProceedFinishGame();
  void RecalculateDeviations();
  static void CollideCars(Car* car_1, Car* car_2);

  static constexpr double kVelocityDecrease = 0.5;
  static constexpr double kDeviationDecrease = 0.5;
  static constexpr double kHPDecrease = 0.005;
  static constexpr double kMinVisibleVelocity = 5;

  Map map_;
  std::vector<Car> cars_;
  std::vector<CarAchievements> car_achievements_;
  std::set<uint32_t> remaining_cars_;
  GameMode* game_mode_ = nullptr;
  WeaponHandler weapon_handler_;
  std::vector<WrapperBase<GameObject>*> game_objects_;
  Line finish_line_;
};
