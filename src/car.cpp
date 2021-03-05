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
  CalculateVelocity();
  Move(time_millisec);
}

void Car::ProceedInput() {
  if(flag_left_) {
    front_wheels_.SetAngle(this->angle_ + kFrontWheelAngle);
  }
  if(flag_right_) {
    front_wheels_.SetAngle(this->angle_ - kFrontWheelAngle);
  }
  if(flag_up_) {
    front_wheels_.SetRotationalSpeed(front_wheels_.GetRotationalSpeed() + kAccelSpeed);
  }
  if(flag_down_) {
    front_wheels_.SetRotationalSpeed(front_wheels_.GetRotationalSpeed() - kAccelSpeed);
  }
}
void Car::CalculateTotalForce() {
  Vec2f front_wheel_force = front_wheels_.CalculateForce();
  Vec2f back_wheel_force = rear_wheels_.CalculateForce();
  total_force_ = front_wheel_force + back_wheel_force;
}

void Car::CalculateVelocity() {

}
void Car::CalculateAngularMomentum() {

}
void Car::Move(int time_millisec) {

}
