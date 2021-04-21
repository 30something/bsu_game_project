#pragma once

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
#include "src/GameCore/Behaviors/first_player_behavior.h"
#include "src/GameCore/Behaviors/second_player_behavior.h"
#include "src/GameCore/Behaviors/bot_behavior.h"
#include "input_controller.h"
#include "src/helpers/wrapper_template.h"

class GameController {
 public:
  explicit GameController(GameMode* game_mode, InputController*);
  ~GameController() = default;

  void Tick(int time_millis);

  std::vector<WrapperBase<GameObject>*> GetGameObjects() const;
  std::vector<Vec2f> GetPlayersCarPositions() const;

 private:
  Map map_;
  std::vector<Car> cars_;
  std::vector<std::vector<QPoint>> borders_;
  std::vector<Vec2f> waypoints_;
  std::vector<Line> no_go_lines_;
  GameMode* game_mode_ = nullptr;
  WeaponHandler weapon_handler_;
  std::vector<WrapperBase<GameObject>*> game_objects_;

  static constexpr double kVelocityDecrease = 1;
  static constexpr double kDeviationDecrease = 0.5;
  static constexpr double kHPDecrease = 0.005;

  void ProceedCollisionsWithCars();
  static void CollideCars(Car* car_1, Car* car_2);
};
