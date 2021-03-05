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
Vec2f Wheel::CalculateForce() {
  Vec2f force{0.0,0.0};
  force.SetAngle(this->angle_);
  force.SetLength(this->applied_mass_ * this->adhesion_coefficient_);
  return force;
}
