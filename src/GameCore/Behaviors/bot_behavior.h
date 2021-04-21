#pragma once

#include <utility>

#include "behavior.h"
#include "src/GameCore/GameObjects/game_object.h"
#include "src/GameCore/GameObjects/car.h"
#include "src/GameCore/GameObjects/mine.h"
#include "src/GameCore/GameObjects/bonus.h"
#include "src/helpers/physics.h"

class BotBehavior : public Behavior {
 public:
  explicit BotBehavior(const std::vector<std::vector<QPoint>>* borders,
                       const std::vector<Car>* cars,
                       const std::vector<Vec2f>*  waypoints,
                       const std::vector<Line>*  no_go_lines);
  void HandleTick(const GameObject* our_car) override;

 private:
  const std::vector<std::vector<QPoint>>* borders_;
  const std::vector<Car>* cars_;
  const std::vector<Vec2f>* waypoints_;
  const std::vector<Line>* no_go_lines_;
  const Car* car_ = nullptr;
  double front_distance_ = 0;
  double left_distance_ = 0;
  double right_distance_ = 0;
  size_t closest_index_ = 0;
  void ProceedDistancesToBorders();
  double FindMinDistanceToBorder(Vec2f angle_vec, Vec2f car_position);
  size_t FindIndexOfClosestWaypoint(const Car& car) const;
  void ProceedDistanceToPlayerCar();
  bool CheckCarInDirection(Line shooting_trajectory) const;
  bool AnyCarInFront() const;
  bool AnyCarInBack() const;
  void ProceedCarFlags();
  static constexpr double kDistanceRange = 100000;
  static constexpr double kWeaponsRange = 100;
  static constexpr double kSpeedCoefficientMultiplier = 2;

  void ProceedIfCorrectDirection();
};