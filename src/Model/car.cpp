#include "car.h"

Car::Car(double speed, double angular_velocity) {
  position_.Set(3.0, 40.0);
  angle_vec_.Set(1.0, 0.0);
  velocity_ = angle_vec_ * speed;
  angular_velocity_ = angular_velocity;
  steering_angle_ = 0.0;

  UpdateWheelsPosAndOrientation();
  for (auto& wheel : wheels_) {
    wheel.SetPreviousPosition(wheel.GetPosition());
  }
}

void Car::AdvanceStep(int time_millisec) {
  double time_sec = time_millisec / 1000.0;

  Vec2f accel;
  double angular_accel = 0.0;

  for (int i = 0; i < 4; i++) {
    if (i == 0 || i == 1) {
      wheels_[i].CalcLateralForce(max_slip_angle_radians_,
                                  mass_,
                                  front_coef_friction_);
    } else {
      wheels_[i].CalcLateralForce(max_slip_angle_radians_,
                                  mass_,
                                  rear_coef_friction_);
    }
    accel += wheels_[i].GetForce();
    Vec2f car_centre_to_wheel = wheels_[i].GetPosition() - position_;
    double projected_force =
        car_centre_to_wheel.AngleBetween(wheels_[i].GetForce())
            * wheels_[i].GetForce().GetLength();
    double torque = projected_force * car_centre_to_wheel.GetLength();
    angular_accel -= torque;
  }
  accel *= 1.0 / mass_;
  angular_accel /= moment_inertia_;

  velocity_ += accel * time_sec;
  angular_velocity_ += angular_accel * time_sec;

  position_ += velocity_ * time_sec;
  angle_vec_.Rotate(angular_velocity_ * time_sec);
  angle_vec_.Normalize();
  UpdateWheelsPosAndOrientation();
}

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
    velocity_ += angle_vec_ * k_accel_factor;
    if (velocity_.GetLength() > max_speed_forward) {
      velocity_.SetLen(max_speed_forward);
    }
  }
  if (flag_down_) {
    velocity_ -= angle_vec_ * k_accel_factor;
    if (velocity_.GetLength() > max_speed_backward &&
        velocity_.GetAngleDegrees() - angle_vec_.GetAngleDegrees() < 89) {
      velocity_.SetLen(max_speed_backward);
    }
  }
}

void Car::Tick(int time_millisec) {
  ProceedInputFlags();
  AdvanceStep(time_millisec);
}

void Car::UpdateWheelsPosAndOrientation() {
  for (auto& wheel : wheels_) {
    wheel.SetPreviousPosition(wheel.GetPosition());
  }

  const Vec2f right(angle_vec_.GetY(), -angle_vec_.GetX());
  wheels_[0].SetPosition(
      position_ + angle_vec_ * half_wheel_base_ - right * half_front_track_);
  wheels_[1].SetPosition(
      wheels_[0].GetPosition() + right * half_front_track_ * 2.0);
  wheels_[2].SetPosition(
      position_ - angle_vec_ * half_wheel_base_ + right * half_rear_track_);
  wheels_[3].SetPosition(
      wheels_[2].GetPosition() - right * half_rear_track_ * 2.0);

  for (int i = 0; i < 4; i++) {
    wheels_[i].SetFront(angle_vec_);
  }

  // Calculated different angles for each front_ wheel using the Ackerman
  // principle. https://en.wikipedia.org/wiki/Ackermann_steering_geometry
  double cornerRadius = length_ / tan(fabs(steering_angle_));
  double outerWheelAngle =
      atan(length_ / (cornerRadius + half_front_track_ * 2.0));
  if (steering_angle_ > 0.0) {
    wheels_[0].Front().Rotate(std::min(steering_angle_, max_steering_lock_));
    wheels_[1].Front().Rotate(std::min(outerWheelAngle, max_steering_lock_));
  } else {
    wheels_[0].Front().Rotate(std::min(-outerWheelAngle, max_steering_lock_));
    wheels_[1].Front().Rotate(std::min(steering_angle_, max_steering_lock_));
  }
}

int Car::GetX() const {
  return position_.GetX();
}

int Car::GetY() const {
  return position_.GetY();
}

double Car::GetAngle() const {
  return angle_vec_.GetAngleDegrees() + 90;
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
