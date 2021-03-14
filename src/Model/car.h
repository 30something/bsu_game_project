//  Kindly taken from https://github.com/abainbridge/car_sim
#pragma once

#include <vector>
#include <iostream>
#include <algorithm>
#include <cmath>

#include "src/helpers/vec2f.h"
#include "wheel.h"

class Car {
 public:
  Car(double speed, double angular_velocity);
  ~Car() = default;

  void Tick(int time_millisec);

  int GetX() const;
  int GetY() const;
  double GetAngle() const;

  void SetFlagUp(bool flag_up);
  void SetFlagDown(bool flag_down);
  void SetFlagLeft(bool flag_left);
  void SetFlagRight(bool flag_right);

 private:
  Vec2f position_;
  Vec2f angle_vec_;
  Vec2f velocity_;
  double angular_velocity_;
  double steering_angle_;

  bool flag_up_ = false;
  bool flag_down_ = false;
  bool flag_left_ = false;
  bool flag_right_ = false;

  std::vector<Wheel> wheels_{4};
  double k_accel_factor = 10.0;
  double max_speed_forward = 300;
  double max_speed_backward = 100;
  double half_front_track_ = 0.75;
  double max_steering_lock_ = 0.7;
  double half_rear_track_ = half_front_track_;
  double half_wheel_base_ = 5.5;
  double length_ = 18.0;
  double mass_ = 1000.0;
  double moment_inertia_ =
      (mass_ * length_ * length_) / 1.0;
  double front_coef_friction_ = 100;
  double rear_coef_friction_ = 80;

  double max_slip_angle_radians_ = 0.07;

  void ProceedInputFlags();
  void UpdateWheelsPosAndOrientation();
  void AdvanceStep(int time_millisec);
};
