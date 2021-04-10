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
  const std::vector<QPoint>& GetMinesCoordinates() const;

  int GetLapsCounter(int index) const;
  double GetVelocity(int index) const;
  int GetWonCar() const;

 private:
  void ProceedCollisionsWithCars();
  void ProceedCollisionsWithFinish();
  void ProceedFinishGame();
  double CalculateFinishDeviation(size_t index);
  static void CollideCars(Car* car_1, Car* car_2);

  static constexpr double kVelocityDecrease = 0.5;
  static constexpr double kDeviationDecrease = 0.5;
  static constexpr double kHPDecrease = 0.005;
  static constexpr double kMinVisibleVelocity = 5;

  enum class FinishCollisionStatus {
    kCollide,
    kNotCollide,
  };

  Map map_;
  std::vector<Car> cars_;
  std::vector<int> laps_counters_;
  std::vector<double> finish_deviations_;
  std::vector<FinishCollisionStatus> finish_collision_statuses_;
  GameMode* game_mode_ = nullptr;
  WeaponHandler weapon_handler_;

  Line finish_line_;
  int number_of_won_car_ = -1;
};
