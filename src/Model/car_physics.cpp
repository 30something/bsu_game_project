#include "car_physics.h"

CarPhysics::CarPhysics(int x,
                       int y,
                       double angle,
                       std::vector<std::vector<std::pair<int, int>>>* borders) :
    borders_(borders),
    prev_position_list_(kSizeOfPreviousPos, position_),
    prev_angle_vec_list_(kSizeOfPreviousPos, angle_vec_) {
  position_.Set(x, y);
  angle_vec_.Set(1.0, 0.0);
  angle_vec_.Rotate(angle);
  UpdateWheelsPosAndOrientation();
  for (auto& wheel : wheels_) {
    wheel.SetPreviousPosition(wheel.GetPosition());
  }
}

void CarPhysics::AdvanceStep(int time_millisec) {
  double time_sec = time_millisec / 1000.0;

  Vec2f accel;
  double angular_accel = 0.0;

  CalcAccelerations(&accel, &angular_accel);
  ProceedCollisions();
  accel *= 1.0 / mass_;
  angular_accel /= moment_inertia_;
  velocity_ += accel * time_sec;
  angular_velocity_ += angular_accel * time_sec;

  // calculate vector of previous positions for collisions
  for (size_t i = 0; i < kSizeOfPreviousPos - 1; i++) {
    prev_position_list_[i] = prev_position_list_[i + 1];
    prev_angle_vec_list_[i] = prev_angle_vec_list_[i + 1];
  }
  prev_position_list_[kSizeOfPreviousPos - 1] = position_;
  prev_angle_vec_list_[kSizeOfPreviousPos - 1] = angle_vec_;

  position_ += velocity_ * time_sec;
  angle_vec_.Rotate(angular_velocity_ * time_sec);
  angle_vec_.Normalize();
  UpdateWheelsPosAndOrientation();
}

void CarPhysics::CalcAccelerations(Vec2f* accel, double* angular_accel) {
  for (int i = 0; i < 4; i++) {
    wheels_[0].CalcLateralForce(max_slip_angle_radians_,
                                mass_,
                                front_coef_friction_);
    wheels_[1].CalcLateralForce(max_slip_angle_radians_,
                                mass_,
                                front_coef_friction_);
    wheels_[2].CalcLateralForce(max_slip_angle_radians_,
                                mass_,
                                rear_coef_friction_);
    wheels_[3].CalcLateralForce(max_slip_angle_radians_,
                                mass_,
                                rear_coef_friction_);
    *accel += wheels_[i].GetForce();
    Vec2f car_centre_to_wheel = wheels_[i].GetPosition() - position_;
    double projected_force =
        car_centre_to_wheel.AngleBetween(wheels_[i].GetForce())
            * wheels_[i].GetForce().GetLength();
    double torque = projected_force * car_centre_to_wheel.GetLength();
    *angular_accel -= torque;
  }
}

void CarPhysics::ProceedCollisions() {
  std::vector<Vec2f> corners =
      {wheels_[0].GetPosition(),
       wheels_[1].GetPosition(),
       wheels_[2].GetPosition(),
       wheels_[3].GetPosition()};
  // For every line of the car find the interceptions
  // with every line of the borders
  for (int i = 0; i < 4; i++) {
    Line l1;
    if (i == 0 || i == 1) {
      l1.x1 = corners[i].GetX();
      l1.y1 = corners[i].GetY();
      l1.x2 = corners[i + 2].GetX();
      l1.y2 = corners[i + 2].GetY();
    }
    if (i == 2 || i == 3) {
      l1.x1 = corners[i - 2].GetX();
      l1.y1 = corners[i - 2].GetY();
      l1.x2 = corners[i].GetX();
      l1.y2 = corners[i].GetY();
    }
    for (const auto& border : *borders_) {
      for (size_t j = 0; j < border.size(); j++) {
        Line l2;
        if (j == border.size() - 1) {
          l2.x1 = border[j].first;
          l2.y1 = border[j].second;
          l2.x2 = border[0].first;
          l2.y2 = border[0].second;
        } else {
          l2.x1 = border[j].first;
          l2.y1 = border[j].second;
          l2.x2 = border[j + 1].first;
          l2.y2 = border[j + 1].second;
        }
        if (Line::IsIntersects(l1, l2)) {
          position_ = prev_position_list_[0];
          angle_vec_ = prev_angle_vec_list_[0];
          velocity_.SetLen(0.0000000001);
          break;
        }
      }
    }
  }
}

void CarPhysics::UpdateWheelsPosAndOrientation() {
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

int CarPhysics::GetX() const {
  return static_cast<int>(position_.GetX());
}

int CarPhysics::GetY() const {
  return static_cast<int>(position_.GetY());
}

double CarPhysics::GetAngle() const {
  return angle_vec_.GetAngleDegrees() + 90;
}

