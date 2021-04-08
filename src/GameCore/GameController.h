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

class GameController {
 public:
  explicit GameController(GameMode* game_mode);
  ~GameController() = default;

  void Tick(int time_millis);

  void HandleKeyPressEvent(QKeyEvent* event);
  void HandleKeyReleaseEvent(QKeyEvent* event);
  const std::vector<Car>& GetCars() const;
  const std::vector<QPoint>& GetMines() const;

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
