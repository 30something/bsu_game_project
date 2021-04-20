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
  explicit BotBehavior(std::vector<std::vector<QPoint>> borders,
                       const std::vector<Car>* cars,
                       const std::vector<Bonus>* bonuses,
                       const std::vector<Mine>* mines,
                       const std::vector<Vec2f>& waypoints,
                       const std::vector<Line>& no_go_lines);
  void HandleTick(const GameObject* our_car) override;

 private:
  std::vector<std::vector<QPoint>> borders_;
  const std::vector<Car>* cars_;
  const std::vector<Bonus>* bonuses_;
  const std::vector<Mine>* mines_;
  std::vector<Vec2f> waypoints_;
  std::vector<Line> no_go_lines_;
  const Car* car_ = nullptr;
  double front_distance_ = 0;
  double back_distance_ = 0;
  double left_distance_ = 0;
  double right_distance_ = 0;
  void ProceedDistancesToBorders();
  double FindMinDistanceToBorder(Vec2f angle_vec, Vec2f car_position);
  size_t FindIndexOfClosestWaypoint();
  bool AnyCarInFront() const;
  bool AnyCarInBack() const;
  void ProceedCarFlags();
  static constexpr double kDistanceRange = 100000;
  static constexpr double kShootingRange = 300;
  static constexpr double kMineRange = 100;
};