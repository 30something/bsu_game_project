#pragma once

#include "helpers/vec_geometry.h"

class Wheel {
 public:
  explicit Wheel(double applied_mass);
  ~Wheel() = default;
 private:
  double adhesion_coefficient_ = 0.0;
  double rotational_speed_ = 0.0;
  Vec2f adhesion_force_{0.0,0.0};
  double applied_mass_ = 0.0;
  double angle_ = 0.0;

 public:
  void SetAngle(double angle);
  void SetRotationalSpeed(double rotational_speed);
  double GetRotationalSpeed() const;
  Vec2f CalculateForce(Vec2f velocity) const;

};
