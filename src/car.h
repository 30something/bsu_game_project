#pragma once

#include "helpers/vec_geometry.h"
#include "wheel.h"

class Car {
 public:
  Car(int x, int y, double mass, double angle);
  ~Car() = default;

  void Tick(int time_millisec);

 private:
  const double kFrontWheelAngle = 1.0;
  const double kAccelSpeed = 10.0;
  int length_ = 10;
  int width_ = 10;
  int x_position_ = 0;
  int y_position_ = 0;
  double angle_ = 0.0;
  double current_power_ = 0.0;
  double mass_ = 1000000.0;
  double moment_of_inertia_ = 1000000;
  double max_forward_speed_ = 10.0;
  double max_backward_speed_ = 10.0;
  Vec2f velocity_{0.0, 0.0};
  double angular_speed_ = 0.0;
  Vec2f total_force_{0.0, 0.0};
  Wheel front_wheels_{mass_ / 2.};
  Wheel rear_wheels_{mass_ / 2.};
  bool flag_up_ = false;
  bool flag_down_ = false;
  bool flag_left_ = false;
  bool flag_right_ = false;

 public:
  int GetX() const;
  int GetY() const;
  double GetAngle() const;

  void SetFlagUp(bool flag_up);
  void SetFlagDown(bool flag_down);
  void SetFlagLeft(bool flag_left);
  void SetFlagRight(bool flag_right);

 private:
  void ProceedInput();
  void CalculateTotalForce();
  void CalculateAngularSpeed(int time_millisec);
  void CalculateVelocity(int time_millisec);

  void Move(int time_millisec);
};

