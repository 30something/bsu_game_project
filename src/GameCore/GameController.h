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
#include "src/helpers/json_parser.h"

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
  const QPoint car1_start_pos_ = {360, 548};
  const double car1_start_angle_ = -M_PI / 2;
  const QPoint car2_start_pos_ = {380, 590};
  const double car2_start_angle_ = -M_PI / 2;
  static constexpr double kVelocityDecrease = 0.5;
  static constexpr double kDeviationDecrease = 0.5;
  static constexpr double kHPDecrease = 0.005;

  JsonOurParser parser;
  Map map_;
  std::vector<Car> cars_;
  GameMode* game_mode_ = nullptr;
  WeaponHandler weapon_handler_;
  void ProceedCollisionsWithCars();
  static void CollideCars(Car* car_1, Car* car_2);
};
