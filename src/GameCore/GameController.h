#pragma once

#include <utility>
#include <vector>

#include <QKeyEvent>
#include <QTextStream>
#include <QFile>
#include <QPoint>

#include "car.h"
#include "map.h"

class GameController {
 public:
  explicit GameController(GameMode* game_mode);
  ~GameController() = default;

  void Tick(int time_millis);

  void HandleKeyPressEvent(QKeyEvent* event);
  void HandleKeyReleaseEvent(QKeyEvent* event);

  std::vector<QPoint> GetCarCoordinates() const;
  std::vector<double> GetCarAngles() const;
  int GetLapsCounter(int index) const;
  double GetVelocity(int index) const;

 private:
  void ProceedCollisionsWithCars();
  void ProceedCollisionsWithFinish();

  static void CollideCars(Car* car_1, Car* car_2);
  double CalculateFinishDeviation(size_t index);

  const QPoint car1_start_pos_ = {360, 548};
  const double car1_start_angle_ = -M_PI / 2;
  const QPoint car2_start_pos_ = {380, 590};
  const double car2_start_angle_ = -M_PI / 2;
  static constexpr double kVelocityDecrease = 0.5;
  static constexpr double kDeviationDecrease = 0.5;
  static constexpr double kMinVisibleVelocity = 5.0;

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
  Line finish_line_;
};
