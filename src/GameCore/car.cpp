#include "car.h"

Car::Car(int x,
         int y,
         double angle,
         Map* map) :
    map_(map),
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

void Car::ProceedInputFlags() {
  if (flag_left_) {
    steering_angle_ = -kMaxSteeringLock;
  }
  if (flag_right_) {
    steering_angle_ = kMaxSteeringLock;
  }
  if (!flag_right_ && !flag_left_) {
    steering_angle_ = 0;
  }
  // TODO(dima_makarov): fix keyboard controls
  if (flag_up_) {
    velocity_ += angle_vec_ * kAccelFactor;
    if (velocity_.GetLength() > kMaxSpeedForward) {
      velocity_.SetLen(kMaxSpeedForward);
    }
  }
  if (flag_down_) {
    velocity_ -= angle_vec_ * kAccelFactor;
    if (velocity_.GetLength() > kMaxSpeedBackward &&
        std::abs(velocity_.GetAngleDegrees() - angle_vec_.GetAngleDegrees())
            < 90) {
      velocity_.SetLen(kMaxSpeedBackward);
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

void Car::AdvanceStep(int time_millisec) {
  double time_sec = time_millisec / 1000.0;

  Vec2f accel;
  double angular_accel = 0.0;

  CalcAccelerations(&accel, &angular_accel);
  ProceedCollisions();
  accel *= 1.0 / kMass;
  angular_accel /= MomentInertia;
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

void Car::CalcAccelerations(Vec2f* accel, double* angular_accel) {
  for (int i = 0; i < 4; i++) {
    CalcLateralForces();
    *accel += wheels_[i].GetForce();
    Vec2f car_centre_to_wheel = wheels_[i].GetPosition() - position_;
    double projected_force =
        car_centre_to_wheel.AngleBetween(wheels_[i].GetForce())
            * wheels_[i].GetForce().GetLength();
    double torque = projected_force * car_centre_to_wheel.GetLength();
    *angular_accel -= torque;
  }
}

void Car::CalcLateralForces() {
  wheels_[0].CalcLateralForce(kMaxSlipAngleRadians,
                              kMass,
                              FrontCoefFriction);
  wheels_[1].CalcLateralForce(kMaxSlipAngleRadians,
                              kMass,
                              FrontCoefFriction);
  wheels_[2].CalcLateralForce(kMaxSlipAngleRadians,
                              kMass,
                              kRearCoefFriction);
  wheels_[3].CalcLateralForce(kMaxSlipAngleRadians,
                              kMass,
                              kRearCoefFriction);
}

void Car::ProceedCollisions() {
  std::vector<Vec2f> corners =
      {wheels_[0].GetPosition(),
       wheels_[1].GetPosition(),
       wheels_[2].GetPosition(),
       wheels_[3].GetPosition()};
  if(map_->ProceedCollisions(corners)) {
    position_ = prev_position_list_[0];
    angle_vec_ = prev_angle_vec_list_[0];
    velocity_.SetLen(0.0000000001);
  }
}

void Car::UpdateWheelsPosAndOrientation() {
  for (auto& wheel : wheels_) {
    wheel.SetPreviousPosition(wheel.GetPosition());
  }

  const Vec2f right(angle_vec_.GetY(), -angle_vec_.GetX());
  wheels_[0].SetPosition(
      position_ + angle_vec_ * kHalfWheelBase - right * kHalfFrontTrack_);
  wheels_[1].SetPosition(
      wheels_[0].GetPosition() + right * kHalfFrontTrack_ * 2.0);
  wheels_[2].SetPosition(
      position_ - angle_vec_ * kHalfWheelBase + right * kHalfRearTrack);
  wheels_[3].SetPosition(
      wheels_[2].GetPosition() - right * kHalfRearTrack * 2.0);

  for (int i = 0; i < 4; i++) {
    wheels_[i].SetFront(angle_vec_);
  }

  // Calculated different angles for each front_ wheel using the Ackerman
  // principle. https://en.wikipedia.org/wiki/Ackermann_steering_geometry
  double cornerRadius = kLength / tan(fabs(steering_angle_));
  double outerWheelAngle =
      atan(kLength / (cornerRadius + kHalfFrontTrack_ * 2.0));
  if (steering_angle_ > 0.0) {
    wheels_[0].Front().Rotate(std::min(steering_angle_, kMaxSteeringLock));
    wheels_[1].Front().Rotate(std::min(outerWheelAngle, kMaxSteeringLock));
  } else {
    wheels_[0].Front().Rotate(std::min(-outerWheelAngle, kMaxSteeringLock));
    wheels_[1].Front().Rotate(std::min(steering_angle_, kMaxSteeringLock));
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
