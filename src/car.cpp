#include "car.h"

Car::Car(int x, int y, double mass, double angle) :
    x_position_(x),
    y_position_(y),
    angle_(angle),
    mass_(mass) {
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

int Car::GetX() const {
  return x_position_;
}

int Car::GetY() const {
  return y_position_;
}

void Car::Tick(int time_millisec) {
  ProceedInput();
  CalculateTotalForce();
  CalculateAngularSpeed(time_millisec);
  CalculateVelocity(time_millisec);
  Move(time_millisec);
}

void Car::ProceedInput() {
  if (flag_left_) {
    front_wheels_.SetAngle(this->angle_ + kFrontWheelAngle);
  }
  if (flag_right_) {
    front_wheels_.SetAngle(this->angle_ - kFrontWheelAngle);
  }
  if (flag_up_) {
    front_wheels_.SetRotationalSpeed(
        front_wheels_.GetRotationalSpeed() + kAccelSpeed);
  }
  if (flag_down_) {
    front_wheels_.SetRotationalSpeed(
        front_wheels_.GetRotationalSpeed() - kAccelSpeed);
  }
}
void Car::CalculateTotalForce() {
  Vec2f front_wheel_force = front_wheels_.CalculateForce(velocity_);
  Vec2f back_wheel_force = rear_wheels_.CalculateForce(velocity_);
  total_force_ = front_wheel_force + back_wheel_force;
}

void Car::CalculateVelocity(int time_millisec) {
  total_force_.SetLength(
      total_force_.GetLength() / mass_); // This is now an acceleration
  velocity_.SetLength(
      velocity_.GetLength() + total_force_.GetLength() * time_millisec);
}

void Car::CalculateAngularSpeed(int time_millisec) {
  double angle_difference = this->front_wheels_.GetAngle() - angle_;
  double perpendicular_force =
      front_wheels_.CalculateForce(velocity_).GetLength()
          * sin(angle_difference);
  // TODO pass length of the car as an additional parameter
  double force_momentum = perpendicular_force * 5;
  double angular_acceleration = force_momentum / moment_of_inertia_;
  angular_speed_ += angular_acceleration * time_millisec;
}

void Car::Move(int time_millisec) {
  x_position_ += static_cast<int>(velocity_.GetX()) * time_millisec / 1000;
  y_position_ += static_cast<int>(velocity_.GetY()) * time_millisec / 1000;
  velocity_.SetAngle(velocity_.GetAngle() + angular_speed_ * time_millisec);
  angle_ = velocity_.GetAngle();
}

double Car::GetAngle() const {
  return angle_;
}
