#include "wheel.h"

void Wheel::CalcLateralForce(double maxSlipAngleRadians,
                             double mass,
                             double friction_coefficient) {
  Vec2f move_since_last_update = position_ - previous_position_;
  move_since_last_update.Normalize();

  double slip_angle = move_since_last_update.AngleBetween(front_);
  slip_angle = std::min(slip_angle, maxSlipAngleRadians);
  slip_angle = std::max(slip_angle, -maxSlipAngleRadians);

  double fraction_of_max_lateral_force = slip_angle / maxSlipAngleRadians;
  double weight_on_wheel = mass * 9.81 / 4.0;
  double force_magnitude =
      fraction_of_max_lateral_force * weight_on_wheel * friction_coefficient;
  force_ = front_.GetPerpendicular() * force_magnitude;
}
