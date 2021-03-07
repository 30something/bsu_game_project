#pragma once

#include <algorithm>

#include "helpers/vec2f.h"

class Wheel {
 public:
  Vec2f previous_position;
  Vec2f position;
  Vec2f front;
  Vec2f force;

  void CalcLateralForce(double maxSlipAngleRadians,
                        double mass,
                        double friction_coefficient) {
    Vec2f move_since_last_update = position - previous_position;
    move_since_last_update.Normalize();

    double slip_angle = move_since_last_update.AngleBetween(front);
    slip_angle = std::min(slip_angle, maxSlipAngleRadians);
    slip_angle = std::max(slip_angle, -maxSlipAngleRadians);

    double fraction_of_max_lateral_force = slip_angle / maxSlipAngleRadians;
    double weight_on_wheel = mass * 9.81 / 4.0;
    double force_magnitude =
        fraction_of_max_lateral_force * weight_on_wheel * friction_coefficient;
    force = front.GetPerpendicular() * force_magnitude;
  }
};
