//  Kindly taken from https://github.com/abainbridge/car_sim
#pragma once

#include <vector>
#include <algorithm>
#include <cmath>
#include <utility>

#include "src/helpers/vec2f.h"
#include "wheel.h"
#include "src/helpers/line.h"

class Car {
 public:
  Car(int x,
      int y,
      double angle);
  ~Car() = default;

  void Tick(int time_millisec);

  int GetX() const;
  int GetY() const;
  double GetAngle() const;
  std::vector<Line> GetLines();

  void SetFlagUp(bool flag_up);
  void SetFlagDown(bool flag_down);
  void SetFlagLeft(bool flag_left);
  void SetFlagRight(bool flag_right);

  void SetIsCollidingWithBorders(bool is_colliding_with_borders);
  void SetIsCollidingWithCar(bool is_colliding_with_car);

 private:
  std::vector<Wheel> wheels_{4};
  Vec2f position_;
  Vec2f angle_vec_;
  Vec2f velocity_;
  double angular_velocity_ = 0;

  std::vector<Vec2f> prev_position_list_;

  std::vector<Vec2f> prev_angle_vec_list_;
  static constexpr int kSizeOfPreviousPos = 4;
  double steering_angle_ = 0;
  static constexpr double kAccelFactor = 2.0;
  static constexpr double kMaxSpeedForward = 300;
  static constexpr double kMaxSpeedBackward = 100;
  static constexpr double kHalfFrontTrack_ = 5.5;
  static constexpr double kMaxSteeringLock = 0.7;
  static constexpr double kHalfRearTrack = kHalfFrontTrack_;
  static constexpr double kHalfWheelBase = 5.5;
  static constexpr double kLength = 18.0;
  static constexpr double kMass = 1000.0;
  static constexpr double MomentInertia = (kMass * kLength * kLength) / 1.0;

  static constexpr double FrontCoefFriction = 100;

  static constexpr double kRearCoefFriction = 80;
  static constexpr double kMaxSlipAngleRadians = 0.07;
  bool flag_up_ = false;
  bool flag_down_ = false;
  bool flag_left_ = false;
  bool flag_right_ = false;
  bool is_colliding_with_car_ = false;
  bool is_colliding_with_borders_ = false;

 private:
  void ProceedCollisions();
  void UpdateWheelsPosAndOrientation();
  void AdvanceStep(int time_millisec);
  void CalcAccelerations(Vec2f* accel, double* angular_accel);
  void ProceedInputFlags();
  void CalcLateralForces();
};
