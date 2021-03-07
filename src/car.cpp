#include <algorithm>

#include <helpers/vector_2.h>
#include "car.h"

Car::Car(double speed, double angVel) {
  position.Set(3.0, 40.0);
  angle_vec_.Set(1.0, 0.0);
  velocity_ = angle_vec_ * speed;
  angular_velocity_ = angVel;
  steering_angle_ = 0.0;

  UpdateWheelsPosAndOrientation();
  for (int i = 0; i < 4; i++) {
    wheels_[i].m_prevPos = wheels_[i].m_pos;
  }
}

void Car::AdvanceStep(int time_millisec) {
  double time_sec = time_millisec / 1000.0;
  // Calculate forces, acceleration and angular acceleration.
  Vector2 accel;
  double angularAccel = 0.0;
  for (int i = 0; i < 4; i++) {
    wheels_[i].CalcLateralForce(max_slip_angle_radians_, mass_, coef_friction_);
    accel += wheels_[i].m_force;

    Vector2 carCentreToWheel = wheels_[i].m_pos - position;
    double projectedForce = carCentreToWheel.AngleBetween(wheels_[i].m_force)
        * wheels_[i].m_force.GetLength();
    double torque = projectedForce * carCentreToWheel.GetLength();
    angularAccel -= torque;
  }
  accel *= 1.0 / mass_;
  angularAccel /= moment_inertia_;

  // Update velocity and angular velocity.
  velocity_ += accel * time_sec;
  angular_velocity_ += angularAccel * time_sec;

  // Update position and orientation.
  position += velocity_ * time_sec;

  angle_vec_.Rotate(angular_velocity_ * time_sec);
  angle_vec_.Normalize();
  UpdateWheelsPosAndOrientation();
}

void Car::ProceedInput() {
  // if (flag_left_) {
  //   steering_angle_ -= 0.02;
  //   if (steering_angle_ > max_steering_lock_)
  //     steering_angle_ = max_steering_lock_;
  // }
  // if (flag_right_) {
  //   steering_angle_ += 0.02;
  //   if (steering_angle_ < -max_steering_lock_)
  //     steering_angle_ = -max_steering_lock_;
  // }
  // if(!flag_right_ && !flag_left_) {
  //   if(steering_angle_ < 0) {
  //     steering_angle_ += 0.02;
  //   }
  //   if(steering_angle_ > 0) {
  //     steering_angle_ -= 0.02;
  //   }
  //   if(std::abs(steering_angle_) < 0.02) {
  //     steering_angle_ = 0;
  //   }
  // }
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
    velocity_ += angle_vec_ * (10.0);
    if (velocity_.GetLength() > max_speed_forward) {
      velocity_.SetLen(max_speed_forward);
    }
  }
  if (flag_down_) {
    velocity_ -= angle_vec_ * (10.0);
    if (velocity_.GetLength() > max_speed_backward &&
        velocity_.GetAngleDegrees() - angle_vec_.GetAngleDegrees() < 89) {
      velocity_.SetLen(max_speed_backward);
    }
  }
}

void Car::Tick(int time_millisec) {
  ProceedInput();
  AdvanceStep(time_millisec);
}

void Car::UpdateWheelsPosAndOrientation() {
  for (int i = 0; i < 4; i++) {
    wheels_[i].m_prevPos = wheels_[i].m_pos;
  }

  const Vector2 right(angle_vec_.y, -angle_vec_.x);
  wheels_[0].m_pos =
      position + angle_vec_ * half_wheel_base_ - right * half_front_track_;
  wheels_[1].m_pos = wheels_[0].m_pos + right * half_front_track_ * 2.0;
  wheels_[2].m_pos =
      position - angle_vec_ * half_wheel_base_ + right * half_rear_track_;
  wheels_[3].m_pos = wheels_[2].m_pos - right * half_rear_track_ * 2.0;

  for (int i = 0; i < 4; i++) {
    wheels_[i].m_front = angle_vec_;
  }

  // Calculated different angles for each front wheel using the Ackerman
  // principle. https://en.wikipedia.org/wiki/Ackermann_steering_geometry
  double cornerRadius = length_ / tan(fabs(steering_angle_));
  double outerWheelAngle =
      atan(length_ / (cornerRadius + half_front_track_ * 2.0));
  if (steering_angle_ > 0.0) {
    wheels_[0].m_front.Rotate(steering_angle_);
    wheels_[1].m_front.Rotate(outerWheelAngle);
  } else {
    wheels_[0].m_front.Rotate(-outerWheelAngle);
    wheels_[1].m_front.Rotate(steering_angle_);
  }
}

int Car::GetX() const {
  return position.x;
}
int Car::GetY() const {
  return position.y;
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
