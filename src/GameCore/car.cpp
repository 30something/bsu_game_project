#include "car.h"

Car::Car(int x,
         int y,
         double angle) :
    position_(x, y) {
  velocity_.Set(Physics::kAlmostZero, Physics::kAlmostZero);
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
            > 90) {
      velocity_.SetLen(kMaxSpeedBackward);
    }
  }
  if (!flag_up_ && !flag_down_) {
    Vec2f coef = angle_vec_ * kFrictionFactor;
    if (velocity_.GetLength() < (coef).GetLength()) {
      velocity_.SetLen(Physics::kAlmostZero);
    } else {
      if (std::abs(velocity_.GetAngleDegrees() - angle_vec_.GetAngleDegrees())
          > 90) {
        velocity_ += coef;
      } else {
        velocity_ -= coef;
      }
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
  accel *= 1.0 / kMass;
  angular_accel /= MomentInertia;
  velocity_ += accel * time_sec;
  angular_velocity_ += angular_accel * time_sec;
  if (velocity_.GetLength() > kMinVelocityThreshold) {
    position_ += velocity_ * time_sec;
  }

  if (std::abs(angular_velocity_) > kMinAngularVelocityThreshold) {
    angle_vec_.Rotate(angular_velocity_ * time_sec);
    angle_vec_.Normalize();
  }
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

std::vector<Line> Car::GetLines() const {
  Line l1(wheels_[0].GetPosition(), wheels_[1].GetPosition());
  Line l2(wheels_[0].GetPosition(), wheels_[2].GetPosition());
  Line l3(wheels_[1].GetPosition(), wheels_[3].GetPosition());
  Line l4(wheels_[2].GetPosition(), wheels_[3].GetPosition());
  return {l1, l2, l3, l4};
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

double Car::GetAngle() const {
  return angle_vec_.GetAngleDegrees() + 90;
}

const Vec2f& Car::GetPosition() const {
  return position_;
}

const Vec2f& Car::GetVelocity() const {
  return velocity_;
}

void Car::SetVelocity(const Vec2f& velocity) {
  velocity_ = velocity;
}

void Car::SetPosition(const Vec2f& position) {
  position_ = position;
}

double Car::GetHitPoints() const {
  return hit_points_;
}

double Car::GetBulletsAmount() const {
  return bullets_amount_;
}

double Car::GetMinesAmount() const {
  return mines_amount_;
}

void Car::AddHitPoints(double hit_points) {
  hit_points_ += hit_points;
}

void Car::AddBulletsAmount(double bullets_amount) {
  bullets_amount_ += bullets_amount;
}

void Car::AddMinesAmount(double mines_amount) {
  mines_amount_ += mines_amount;
}

const Vec2f& Car::GetAngleVec() const {
  return angle_vec_;
}

bool Car::IsShooting() const {
  if (bullets_amount_ <= 0) {
    return false;
  }
  return is_shooting_;
}

void Car::SetIsShooting(bool is_shooting) {
  if (bullets_amount_ <= 0) {
    is_shooting_ = false;
  } else {
    is_shooting_ = is_shooting;
  }
}

bool Car::IsAlive() const {
  return is_alive_;
}

void Car::SetIsAlive(bool is_alive) {
  is_alive_ = is_alive;
}

QPoint Car::DropMine(bool* successful) {
  if (mines_amount_ > 0) {
    *successful = true;
    mines_amount_--;
    return QPoint(angle_vec_.GetX() * (kPutMineOffset) + position_.GetX(),
                  angle_vec_.GetY() * (kPutMineOffset) + position_.GetY());
  } else {
    *successful = false;
    return QPoint(0, 0);
  }
}

Line Car::ShootBullet(bool* successful) {
  if (bullets_amount_ > 0) {
    *successful = true;
    bullets_amount_--;
    return Line(
        position_.GetX(),
        position_.GetY(),
        angle_vec_.GetX() * kShootingRange + position_.GetX(),
        angle_vec_.GetY() * kShootingRange + position_.GetY());
  } else {
    *successful = false;
    return Line();
  }
}
