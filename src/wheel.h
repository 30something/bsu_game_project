#pragma once

#include <algorithm>

#include "helpers/vec2f.h"

class Wheel {
 private:
  Vec2f previous_position_;
  Vec2f position_;
  Vec2f front_;
  Vec2f force_;

 public:

  Vec2f& Front() {
    return this->front_;
  }

  const Vec2f& GetPreviousPosition() const {
    return previous_position_;
  }

  void SetPreviousPosition(const Vec2f& previous_position) {
    Wheel::previous_position_ = previous_position;
  }

  const Vec2f& GetPosition() const {
    return position_;
  }

  void SetPosition(const Vec2f& position) {
    Wheel::position_ = position;
  }

  const Vec2f& GetFront() const {
    return front_;
  }

  void SetFront(const Vec2f& front) {
    Wheel::front_ = front;
  }

  const Vec2f& GetForce() const {
    return force_;
  }

  void SetForce(const Vec2f& force) {
    Wheel::force_ = force;
  }

  void CalcLateralForce(double maxSlipAngleRadians,
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
};
