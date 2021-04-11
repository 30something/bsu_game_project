#pragma once

#include <set>
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

  double GetVelocity(int index) const;
  int32_t GetLapsCounter(int index) const;
  bool AllCarsFinished() const;

 private:
  void ProceedCollisionsWithCars();
  void ProceedCollisionsWithFinish();
  void ProceedFinishGame();
  void RecalculateDeviations();
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

  enum class FinishStatus {
    kFinished,
    kNotFinished,
  };

  Map map_;
  std::vector<Car> cars_;
  std::vector<int32_t> laps_counters_;
  std::set<uint32_t> remaining_cars_;
  std::vector<double> finish_deviations_;
  std::vector<FinishCollisionStatus> finish_collision_statuses_;
  std::vector<FinishStatus> finish_statuses_;
  GameMode* game_mode_ = nullptr;
  WeaponHandler weapon_handler_;

  Line finish_line_;
};
