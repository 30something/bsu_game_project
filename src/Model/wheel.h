#pragma once

#include <algorithm>

#include "src/helpers/vec2f.h"

class Wheel {
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
                        double friction_coefficient);

 private:
  Vec2f previous_position_;
  Vec2f position_;
  Vec2f front_;
  Vec2f force_;
};
