//  Kindly taken from https://github.com/abainbridge/car_sim
#pragma once

#include <vector>
#include <iostream>

#include "helpers/vec_geometry.h"
#include "wheel.h"
#include "force.h"

class Car {
 public:
  Car(double speed, double angVel);
  ~Car() = default;

  void Tick(int time_millisec);

 public:
  int GetX() const;
  int GetY() const;
  double GetAngle() const;

  void SetFlagUp(bool flag_up);
  void SetFlagDown(bool flag_down);
  void SetFlagLeft(bool flag_left);
  void SetFlagRight(bool flag_right);

 private:

  Vector2 position;
  Vector2 angle_vec_;
  Vector2 velocity_;
  double angular_velocity_;
  double steering_angle_;

  bool flag_up_;
  bool flag_down_;
  bool flag_left_;
  bool flag_right_;

  std::vector<Wheel> wheels_{4};
  const double max_speed_forward = 300;
  const double max_speed_backward = 100;
  const double half_front_track_ = 0.75;
  const double max_steering_lock_ = 0.7;
  const double half_rear_track_ = half_front_track_;
  const double half_wheel_base_ = 1.165;
  const double length_ = 10.995;
  const double mass_ = 200.0;
  const double moment_inertia_ =
      (mass_ * length_ * length_) / 12.0; // Formula is for a rod.
  const double coef_friction_ = 70;
  const double max_slip_angle_radians_ = 0.07;

  void ProceedInput();
  void UpdateWheelsPosAndOrientation();
  void AdvanceStep(int time_millisec);

};

