#pragma once

#include <utility>
#include <vector>

#include <QKeyEvent>
#include <QTextStream>
#include <QFile>
#include <QPoint>

#include "car.h"
#include "map.h"
#include "weapon_handler.h"
#include "src/helpers/json_map_parser.h"
#include "src/GameCore/CarBehavior/first_player_behavior.h"
#include "src/GameCore/CarBehavior/second_player_behavior.h"
#include "src/GameCore/CarBehavior/input_controller.h"

class GameController {
 public:
  explicit GameController(GameMode* game_mode, InputController*);
  ~GameController() = default;

  void Tick(int time_millis);

  std::vector<const GameObject*> GetCars() const;
  std::vector<const GameObject*> GetMines() const;
  std::vector<const GameObject*> GetBonuses() const;

 private:
  Map map_;
  std::vector<Car> cars_;
  GameMode* game_mode_ = nullptr;
  WeaponHandler weapon_handler_;

  static constexpr double kVelocityDecrease = 0.5;
  static constexpr double kDeviationDecrease = 0.5;
  static constexpr double kHPDecrease = 0.005;

  void ProceedCollisionsWithCars();
  static void CollideCars(Car* car_1, Car* car_2);
};
