#pragma once

#include <utility>
#include <algorithm>
#include <vector>

#include "behavior.h"
#include "src/GameCore/GameObjects/game_object.h"
#include "src/GameCore/GameObjects/car.h"
#include "src/GameCore/GameObjects/mine.h"
#include "src/GameCore/GameObjects/bonus.h"
#include "src/helpers/physics.h"
#include "src/helpers/game_mode.h"

class BotBehavior : public Behavior {
 public:
  explicit BotBehavior(const std::vector<std::vector<QPoint>>& borders,
                       const std::vector<Car>& cars,
                       const std::vector<Vec2f>& waypoints,
                       const std::vector<Line>& no_go_lines,
                       GameMode* gamemode);
  void HandleTick(GameObject* our_car) override;

 private:
  const std::vector<std::vector<QPoint>>& borders_;
  const std::vector<Car>& cars_;
  const std::vector<Vec2f>& waypoints_;
  const std::vector<Line>& no_go_lines_;

  const Car* car_ = nullptr;
  double front_distance_ = 0;
  double left_distance_ = 0;
  double right_distance_ = 0;
  size_t closest_index_ = 0;
  GameMode* game_mode_ = nullptr;

  void ProceedDistancesToBorders();
  double FindMinDistanceToBorder(Vec2f angle_vec, Vec2f car_position);
  size_t FindIndexOfClosestWaypoint(const Car& car) const;
  void ProceedDistanceToPlayerCar();
  bool CheckCarInDirection(Vec2f position, Vec2f angle_vec) const;
  bool AnyCarInFront() const;
  bool AnyCarInBack() const;
  void ProceedCarFlags();
  void ProceedIfCorrectDirection();
  size_t FindClosestPlayersCar();

  static constexpr double kDistanceRange = 100000;
  static constexpr double kWeaponsRange = 100;
  static constexpr double kSpeedCoefficientMultiplier = 10;
  static constexpr double kMinDistanceToTurn = 10;
  static constexpr double kMaxSpeedCoefficient = 100;
  static size_t GetMinimalElementIndex(const std::vector<double>& distances);
};
