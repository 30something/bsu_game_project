#pragma once

#include <utility>

#include "behavior.h"
#include "src/GameCore/game_object.h"
#include "src/GameCore/car.h"
#include "src/helpers/physics.h"


class BotBehavior : public Behavior {
 public:
  explicit BotBehavior(std::vector<std::vector<QPoint>>  borders);
  void HandleTick(GameObject*) override;
  void HandleKeyPressEvent(GameObject*, QKeyEvent*) override;
  void HandleKeyReleaseEvent(GameObject*, QKeyEvent*) override;

 private:
  std::vector<std::vector<QPoint>> borders_;
  double front_distance_ = 0;
  double back_distance_ = 0;
  double left_distance_ = 0;
  double right_distance_ = 0;
  void ProceedDistancesToBorders(Car* car);
  double FindMinDistanceToBorder(Vec2f angle_vec, Vec2f car_position);

  static constexpr double kDistanceRange = 100000;
};
