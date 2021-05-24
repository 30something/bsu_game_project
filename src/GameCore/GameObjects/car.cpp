#include "car.h"
#include "src/helpers/other_constants.h"

Car::Car(Vec2f position,
         double angle,
         Behavior* behavior,
         CarsColors car_color,
         bool enable_drifts) :
    GameObject(position, new CarPixmapComponent),
    behavior_(behavior),
    car_color_(car_color),
    enable_drifts_(enable_drifts) {
  car_pixmap_component_ =
      dynamic_cast<CarPixmapComponent*> (pixmap_component_.get());
  velocity_.Set(physics::kAlmostZero, physics::kAlmostZero);
  angle_vec_.Set(1.0, 0.0);
  angle_vec_.Rotate(angle);
  UpdateWheelsPosAndOrientation();
  for (auto& wheel : wheels_) {
    wheel.SetPreviousPosition(wheel.GetPosition());
  }
  car_pixmap_component_->SetCarPixmapId(CarStates::kStandard, car_color_);
}

void Car::ProceedInputFlagsArcade() {
  if (behavior_->IsFlagLeft()) {
    angle_vec_.Rotate(-kTickRotationAngle);
  }
  if (behavior_->IsFlagRight()) {
    angle_vec_.Rotate(kTickRotationAngle);
  }
  ProceedUpDownFlags();
}

void Car::ArcadeStep(int time_millisec) {
  // Я не знаю почему оно не работает решением в лоб
  // Но я сидел над этим часа два и этот вариант вроде работает всегда
  ProceedInputFlagsArcade();
  double time_sec = time_millisec / 1000.0;
  UpdateWheelsPosAndOrientation();
  double velocity_len = velocity_.GetLength();
  double angle =
      std::abs(velocity_.GetAngleDegrees() - angle_vec_.GetAngleDegrees());
  if (angle > 350 || angle < 90) {
    velocity_ = angle_vec_;
  } else {
    velocity_ = angle_vec_ * -1;
  }
  velocity_.SetLen(velocity_len);
  if (velocity_.GetLength() > kMinVelocityThreshold) {
    position_ += velocity_ * time_sec;
  }
}

void Car::ProceedInputFlagsRealistic() {
  if (behavior_->IsFlagLeft()) {
    steering_angle_ = -kMaxSteeringLock;
  }
  if (behavior_->IsFlagRight()) {
    steering_angle_ = kMaxSteeringLock;
  }
  if (!behavior_->IsFlagRight() && !behavior_->IsFlagLeft()) {
    steering_angle_ = 0;
  }
  ProceedUpDownFlags();
}

void Car::ProceedUpDownFlags() {
  if (behavior_->IsFlagUp()) {
    velocity_ += angle_vec_ * kAccelFactor;
    if (velocity_.GetLength() > behavior_->GetMaxSpeed()) {
      velocity_.SetLen(behavior_->GetMaxSpeed());
    }
  }
  if (behavior_->IsFlagDown()) {
    velocity_ -= angle_vec_ * kAccelFactor;
    if (velocity_.GetLength() > kMaxSpeedBackward &&
        std::abs(velocity_.GetAngleDegrees() - angle_vec_.GetAngleDegrees())
            > 90) {
      velocity_.SetLen(kMaxSpeedBackward);
    }
  }
  if ((!behavior_->IsFlagUp() && !behavior_->IsFlagDown())) {
    Vec2f coef = angle_vec_ * kFrictionFactor;
    if (velocity_.GetLength() < (coef).GetLength()) {
      velocity_.SetLen(physics::kAlmostZero);
    } else {
      velocity_.SetLen(velocity_.GetLength() - coef.GetLength());
    }
  }
}

void Car::Tick(int time_millisec) {
  behavior_->HandleTick(this);
  if (enable_drifts_) {
    RealisticStep(time_millisec);
  } else {
    ArcadeStep(time_millisec);
  }
  if (car_pixmap_component_->GetFramesForChangingHitpoints() == 0) {
    car_pixmap_component_->SetShowingHealthChangeState(false);
  }
  ChoosePixmap();
  mines_tick_timer_++;
  UpdateCollisionLines();
}

void Car::EnableInput(bool flag) {
  behavior_->EnableInput(flag);
}

void Car::RealisticStep(int time_millisec) {
  ProceedInputFlagsRealistic();
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

const std::vector<Line>& Car::GetCollisionLines() const {
  return collision_lines_;
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

const Vec2f& Car::GetVelocity() const {
  return velocity_;
}

std::pair<double, Motion> Car::GetParametersForEngineSound() const {
    double speed_parameter = velocity_.GetLength() / behavior_->GetMaxSpeed();

    if (!(behavior_->IsDead())) {
        if (behavior_->IsFlagDown() && std::abs(velocity_.GetAngleDegrees() -
                                                angle_vec_.GetAngleDegrees()) >
                                       90) {
            speed_parameter = velocity_.GetLength() / kMaxSpeedBackward;
            return std::pair<double, Motion>(speed_parameter,
                                             Motion::kBackwardMotion);
        }
        if (!behavior_->IsFlagUp()) {
            return std::pair<double, Motion>(speed_parameter,
                                             Motion::kWithoutMotion);
        }
        if (behavior_->IsFlagUp()) {
            return std::pair<double, Motion>(speed_parameter,
                                             Motion::kForwardMotion);
        }
    }
    return std::pair<double, Motion>(speed_parameter,
                                     Motion::kIsDead);
}

double Car::GetParameterForDriftSound() const {
    if (!(behavior_->IsDead())) {
        const double kDriftSpeed = 50;
        double relative_velocity =
                velocity_.GetLength() / behavior_->GetMaxSpeed();
        if ((behavior_->IsFlagRight() || behavior_->IsFlagLeft()) &&
            velocity_.GetLength() > kDriftSpeed) {
            if (relative_velocity < 0.1) {
                return 0.1;
            }
            return relative_velocity;
        }
    }
    return 0;
}

double Car::GetParameterForBrakeSound() const {
    if (!(behavior_->IsDead())) {
        const double kSpeedForBrake = 100;
        double relative_velocity =
                velocity_.GetLength() / behavior_->GetMaxSpeed();
        if (behavior_->IsFlagDown() && !behavior_->IsFlagUp() &&
            velocity_.GetLength() > kSpeedForBrake &&
            std::abs(velocity_.GetAngleDegrees() - angle_vec_.GetAngleDegrees())
            <= 90) {
            if (relative_velocity < 0.1) {
                return 0.1;
            }
            return relative_velocity;
        }
    }
    return 0;
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

size_t Car::GetBulletsAmount() const {
  return bullets_amount_;
}

size_t Car::GetMinesAmount() const {
  return mines_amount_;
}

size_t Car::GetColor() const {
  return static_cast<size_t>(car_color_);
}

void Car::AddHitPoints(double hit_points) {
  hit_points_ += hit_points;
  if (std::abs(hit_points) + kEps >= kMinSignificantDamage) {
    car_pixmap_component_->SetShowingHealthChangeState(true);
  } else if (car_pixmap_component_->GetShowingHealthChangeState()) {
    return;
  }
  car_pixmap_component_->SetFramesForChangingHitPoints(
      CarPixmapComponent::kChangingHitPointsAnimationLastFrame);
  health_increasing_state = (hit_points + kEps >= 0);
}

void Car::AddBulletsAmount(size_t bullets_amount) {
  bullets_amount_ += bullets_amount;
}

void Car::AddMinesAmount(size_t mines_amount) {
  mines_amount_ += mines_amount;
}

const Vec2f& Car::GetAngleVec() const {
  return angle_vec_;
}

const Vec2f* Car::GetAngleVecPointer() const {
  return &angle_vec_;
}

bool Car::IsShooting() const {
  if (bullets_amount_ == 0) {
    return false;
  }
  return behavior_->IsFlagShoot();
}

bool Car::UsingGun() const {
    return behavior_->IsFlagShoot();
}

bool Car::IsDead() const {
    return behavior_->IsDead();
}

void Car::BecomeDead() {
  behavior_->EnableInput(false);
  behavior_->SetIsDead();
  car_pixmap_component_->SetCarPixmapId(CarStates::kDead, car_color_);
}

std::optional<Vec2f> Car::DropMine() {
  if (mines_amount_ > 0 && ++mines_tick_timer_ > kMineDelayTicks) {
    mines_amount_--;
    mines_tick_timer_ = 0;
    return Vec2f(angle_vec_.GetX() * (kPutMineOffset) + position_.GetX(),
                 angle_vec_.GetY() * (kPutMineOffset) + position_.GetY());
  } else {
    return std::nullopt;
  }
}

std::optional<Line> Car::ShootBullet() {
  if (bullets_amount_ > 0) {
    bullets_amount_--;
    return Line(
        position_.GetX(),
        position_.GetY(),
        angle_vec_.GetX() * kShootingRange + position_.GetX(),
        angle_vec_.GetY() * kShootingRange + position_.GetY());
  } else {
    return std::nullopt;
  }
}

bool Car::IsPuttingMine() const {
  return behavior_->IsFlagMine() && mines_tick_timer_ >= kMineDelayTicks;
}

void Car::UpdateCollisionLines() {
  collision_lines_[0] =
      Line(wheels_[0].GetPosition(), wheels_[1].GetPosition());
  collision_lines_[1] =
      Line(wheels_[0].GetPosition(), wheels_[2].GetPosition());
  collision_lines_[2] =
      Line(wheels_[1].GetPosition(), wheels_[3].GetPosition());
  collision_lines_[3] =
      Line(wheels_[2].GetPosition(), wheels_[3].GetPosition());
}

void Car::ChoosePixmap() {
  if (car_pixmap_component_->GetShowingHealthChangeState()) {
    car_pixmap_component_->DecrementFramesForChangingHitpoints();
    if (health_increasing_state) {
      car_pixmap_component_->SetCarPixmapId(CarStates::kHealthy, car_color_);
    } else {
      car_pixmap_component_->SetCarPixmapId(CarStates::kDamaged, car_color_);
    }
  } else {
    car_pixmap_component_->SetCarPixmapId(CarStates::kStandard, car_color_);
  }
}

void Car::SetAngleVec(const Vec2f& angle_vec) {
  angle_vec_ = angle_vec;
}

void Car::CarPixmapComponent::SetCarPixmapId(CarStates car_state,
                                             CarsColors car_color) {
  auto category_value = static_cast<int32_t>(PixmapCategories::kCar);
  auto car_state_value = static_cast<int32_t>(car_state);
  auto car_color_value = static_cast<int32_t>(car_color);
  pixmap_id_ = (category_value << 24) + (car_state_value << 16) +
      car_color_value;
}

size_t Car::CarPixmapComponent::GetFramesForChangingHitpoints() const {
  return frames_for_changing_hitpoints_;
}

bool Car::CarPixmapComponent::GetShowingHealthChangeState() const {
  return showing_health_change_state_;
}

void Car::CarPixmapComponent::SetFramesForChangingHitPoints(
    size_t frames_for_changing_hitpoints) {
  frames_for_changing_hitpoints_ = frames_for_changing_hitpoints;
}

void Car::CarPixmapComponent::SetShowingHealthChangeState(
    bool showing_health_change_state) {
  showing_health_change_state_ = showing_health_change_state;
}

void Car::CarPixmapComponent::DecrementFramesForChangingHitpoints() {
  frames_for_changing_hitpoints_--;
}

