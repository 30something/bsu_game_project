#pragma once

#include <utility>

#include "behavior.h"
#include "src/GameCore/game_object.h"
#include "src/GameCore/car.h"
#include "src/GameCore/mine.h"
#include "src/helpers/bonus.h"
#include "src/helpers/physics.h"

class BotBehavior : public Behavior {
 public:
  explicit BotBehavior(std::vector<std::vector<QPoint>> borders,
                       const std::vector<Car>* cars,
                       const std::vector<Bonus>* bonuses,
                       const std::vector<Mine>* mines);
  void HandleTick(GameObject*) override;
  void HandleKeyPressEvent(GameObject*, QKeyEvent*) override;
  void HandleKeyReleaseEvent(GameObject*, QKeyEvent*) override;

 private:
  std::vector<std::vector<QPoint>> borders_;
  const std::vector<Car>* cars_;
  const std::vector<Bonus>* bonuses_;
  const std::vector<Mine>* mines_;
  double front_distance_ = 0;
  double back_distance_ = 0;
  double left_distance_ = 0;
  double right_distance_ = 0;
  void ProceedDistancesToBorders(Car* car);
  double FindMinDistanceToBorder(Vec2f angle_vec, Vec2f car_position);
  bool AnyCarInFront(Car* car) const;
  bool AnyCarInBack(Car* car) const;
  void ProceedCarFlags(Car* car) const;
  static constexpr double kDistanceRange = 100000;
  static constexpr double kShootingRange = 300;
  static constexpr double kMineRange = 100;
};
