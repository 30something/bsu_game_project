#include "wheel.h"

Wheel::Wheel(double applied_mass) : applied_mass_(applied_mass) {
}

void Wheel::SetAngle(double angle) {
  angle_ = angle;
}

double Wheel::GetRotationalSpeed() const {
  return rotational_speed_;
}

void Wheel::SetRotationalSpeed(double rotational_speed) {
  rotational_speed_ = rotational_speed;
}

Vec2f Wheel::CalculateForce(Vec2f velocity) const {
  // Vec2f force_perpend{0.0, 0.0};
  Vec2f force_parallel{0.0, 0.0};
  // force_perpend.SetAngle(velocity.GetAngle() + 180);
  // force_perpend.SetLength(this->applied_mass_ * this->adhesion_coefficient_);
  force_parallel.SetAngle(this->angle_);
  if (this->rotational_speed_ > 0.0001) {
    force_parallel.SetLength(this->applied_mass_ * this->adhesion_coefficient_);
  }
  return force_parallel;
}

double Wheel::GetAngle() const {
  return angle_;
}
