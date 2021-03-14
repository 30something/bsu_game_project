#include "car.h"

Car::Car(int x,
         int y,
         double angle,
         std::vector<std::pair<int, int>>* left_borders,
         std::vector<std::pair<int, int>>* right_borders) :
    left_borders_(left_borders),
    right_borders_(right_borders) {
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
  previous_position_ = position_;
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
      l2.x1 = corners[i-2].GetX();
      l2.y1 = corners[i-2].GetY();
      l2.x2 = corners[i].GetX();
      l2.y2 = corners[i].GetY();
    }
    for (int j = 0; j < left_borders_->size(); j++) {
      Line l1;
      if (j == left_borders_->size() - 1) {
        l1.x1 = (*left_borders_)[j].first;
        l1.y1 = (*left_borders_)[j].second;
        l1.x2 = (*left_borders_)[0].first;
        l1.y2 = (*left_borders_)[0].second;
      } else {
        l1.x1 = (*left_borders_)[j].first;
        l1.y1 = (*left_borders_)[j].second;
        l1.x2 = (*left_borders_)[j + 1].first;
        l1.y2 = (*left_borders_)[j + 1].second;
      }
      if (isIntersects(l1, l2)) {
        QApplication::exit();
        position_ = previous_position_;
        break;
      }
    }
    for (int j = 0; j < right_borders_->size(); j++) {
      Line l1;
      if (j == right_borders_->size() - 1) {
        l1.x1 = (*right_borders_)[j].first;
        l1.y1 = (*right_borders_)[j].second;
        l1.x2 = (*right_borders_)[0].first;
        l1.y2 = (*right_borders_)[0].second;
      } else {
        l1.x1 = (*right_borders_)[j].first;
        l1.y1 = (*right_borders_)[j].second;
        l1.x2 = (*right_borders_)[j + 1].first;
        l1.y2 = (*right_borders_)[j + 1].second;
      }
      if (isIntersects(l1, l2)) {
        QApplication::exit();
        position_ = previous_position_;
        break;
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
  // std::cout << isIntersects(Line(360, 542, 359, 553), Line(356, 354, 635, 244));
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

bool Car::isIntersects(Line l1, Line l2) {
  int ax1 = l1.x1;
  int ay1 = l1.y1;
  int ax2 = l1.x2;
  int ay2 = l1.y2;
  int bx1 = l2.x1;
  int by1 = l2.y1;
  int bx2 = l2.x2;
  int by2 = l2.y2;
  int v1 = (bx2 - bx1) * (ay1 - by1) - (by2 - by1) * (ax1 - bx1);
  int v2 = (bx2 - bx1) * (ay2 - by1) - (by2 - by1) * (ax2 - bx1);
  int v3 = (ax2 - ax1) * (by1 - ay1) - (ay2 - ay1) * (bx1 - ax1);
  int v4 = (ax2 - ax1) * (by2 - ay1) - (ay2 - ay1) * (bx2 - ax1);
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