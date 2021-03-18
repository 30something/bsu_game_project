#include "car.h"

Car::Car(int x,
         int y,
         double angle,
         std::vector<std::vector<std::pair<int, int>>>* borders) :
    borders_(borders),
    prev_position_list_(kSizeOfPreviousPos, position_),
    prev_angle_vec_list_(kSizeOfPreviousPos, angle_vec_){
  position_.Set(x, y);
  angle_vec_.Set(1.0, 0.0);
  angle_vec_.Rotate(angle);
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
  ProceedCollisions();
  accel *= 1.0 / mass_;
  angular_accel /= moment_inertia_;

  velocity_ += accel * time_sec;
  angular_velocity_ += angular_accel * time_sec;

  for(size_t i = 0; i < kSizeOfPreviousPos - 1; i++) {
    prev_position_list_[i] = prev_position_list_[i+1];
    prev_angle_vec_list_[i] = prev_angle_vec_list_[i+1];
  }
  prev_position_list_[kSizeOfPreviousPos - 1] = position_;
  prev_angle_vec_list_[kSizeOfPreviousPos - 1] = angle_vec_;

  position_ += velocity_ * time_sec;
  angle_vec_.Rotate(angular_velocity_ * time_sec);
  angle_vec_.Normalize();
  UpdateWheelsPosAndOrientation();
}

Vec2f Car::ProceedCollisions() {
  Vec2f front_left_corner = wheels_[0].GetPosition();
  Vec2f front_right_corner = wheels_[1].GetPosition();
  Vec2f back_left_corner = wheels_[2].GetPosition();
  Vec2f back_right_corner = wheels_[3].GetPosition();
  std::vector<Vec2f> corners =
      {front_left_corner,
       front_right_corner,
       back_left_corner,
       back_right_corner};
  for (int i = 0; i < 4; i++) {
    Line l2;
    if (i == 0 || i == 1) {
      l2.x1 = corners[i].GetX();
      l2.y1 = corners[i].GetY();
      l2.x2 = corners[i + 2].GetX();
      l2.y2 = corners[i + 2].GetY();
    }
    if (i == 2 || i == 3) {
      l2.x1 = corners[i - 2].GetX();
      l2.y1 = corners[i - 2].GetY();
      l2.x2 = corners[i].GetX();
      l2.y2 = corners[i].GetY();
    }
    for (const auto& border : *borders_) {
      for (size_t j = 0; j < border.size(); j++) {
        Line l1;
        if (j == border.size() - 1) {
          l1.x1 = border[j].first;
          l1.y1 = border[j].second;
          l1.x2 = border[0].first;
          l1.y2 = border[0].second;
        } else {
          l1.x1 = border[j].first;
          l1.y1 = border[j].second;
          l1.x2 = border[j + 1].first;
          l1.y2 = border[j + 1].second;
        }
        if (isIntersects(l1, l2)) {
          position_ = prev_position_list_[0];
          angle_vec_ = prev_angle_vec_list_[0];
          velocity_.SetLen(0.0001);
          break;
        }
      }
    }
  }
  return front_left_corner;
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
    velocity_ += angle_vec_ * accel_factor;
    if (velocity_.GetLength() > max_speed_forward) {
      velocity_.SetLen(max_speed_forward);
    }
  }
  if (flag_down_) {
    velocity_ -= angle_vec_ * accel_factor;
    if (velocity_.GetLength() > max_speed_backward &&
        std::abs(velocity_.GetAngleDegrees() - angle_vec_.GetAngleDegrees()) < 90) {
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
  return static_cast<int>(position_.GetX());
}

int Car::GetY() const {
  return static_cast<int>(position_.GetY());
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

bool Car::isIntersects(Line l1, Line l2) {
  double ax1 = l1.x1;
  double ay1 = l1.y1;
  double ax2 = l1.x2;
  double ay2 = l1.y2;
  double bx1 = l2.x1;
  double by1 = l2.y1;
  double bx2 = l2.x2;
  double by2 = l2.y2;
  double v1 = (bx2 - bx1) * (ay1 - by1) - (by2 - by1) * (ax1 - bx1);
  double v2 = (bx2 - bx1) * (ay2 - by1) - (by2 - by1) * (ax2 - bx1);
  double v3 = (ax2 - ax1) * (by1 - ay1) - (ay2 - ay1) * (bx1 - ax1);
  double v4 = (ax2 - ax1) * (by2 - ay1) - (ay2 - ay1) * (bx2 - ax1);
  bool left;
  bool right;
  if ((v1 < 0 && v2 < 0) || (v1 > 0 && v2 > 0)) {
    left = false;
  } else if ((v1 < 0 && v2 > 0) || (v1 > 0 && v2 < 0)) {
    left = true;
  } else {
    left = false;
  }

  if ((v3 < 0 && v4 < 0) || (v3 > 0 && v4 > 0)) {
    right = false;
  } else if ((v3 < 0 && v4 > 0) || (v3 > 0 && v4 < 0)) {
    right = true;
  } else {
    right = false;
  }

  return left && right;
}