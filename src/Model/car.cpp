#include "car.h"

Car::Car(int x,
         int y,
         double angle,
         std::vector<std::vector<std::pair<int, int>>>* borders) :
    CarPhysics(x, y, angle, borders) {}

void Car::ProceedInputFlags() {
  if (flag_left_) {
    steering_angle_ = -max_steering_lock_;
  }
  if (flag_right_) {
    steering_angle_ = max_steering_lock_;
  }
  if (!flag_right_ && !flag_left_) {
    steering_angle_ = 0;
  }
  // TODO(dima_makarov): fix keyboard controls
  if (flag_up_) {
    velocity_ += angle_vec_ * accel_factor;
    if (velocity_.GetLength() > max_speed_forward) {
      velocity_.SetLen(max_speed_forward);
    }
  }
  if (flag_down_) {
    velocity_ -= angle_vec_ * accel_factor;
    if (velocity_.GetLength() > max_speed_backward &&
        std::abs(velocity_.GetAngleDegrees() - angle_vec_.GetAngleDegrees())
            < 90) {
      velocity_.SetLen(max_speed_backward);
    }
  }
}

void Car::Tick(int time_millisec) {
  ProceedInputFlags();
  AdvanceStep(time_millisec);
}

void Car::SetFlagUp(bool flag_up) {
  flag_up_ = flag_up;
}

void Car::SetFlagDown(bool flag_down) {
  flag_down_ = flag_down;
}

void Car::SetFlagLeft(bool flag_left) {
  flag_left_ = flag_left;
}

void Car::SetFlagRight(bool flag_right) {
  flag_right_ = flag_right;
}
