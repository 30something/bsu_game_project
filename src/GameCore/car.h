//  Kindly taken from https://github.com/abainbridge/car_sim
#pragma once

#include <vector>
#include <algorithm>
#include <cmath>
#include <utility>

#include "src/helpers/vec2f.h"
#include "wheel.h"
#include "src/helpers/line.h"
#include "src/helpers/physics.h"

class Car {
 public:
  Car(int x,
      int y,
      double angle);
  ~Car() = default;

  void Tick(int time_millisec);

  double GetHitPoints() const;
  double GetBulletsAmount() const;
  double GetMinesAmount() const;
  double GetAngle() const;
  std::vector<Line> GetLines() const ;
  const Vec2f& GetVelocity() const;
  const Vec2f& GetPosition() const;
  const Vec2f& GetAngleVec() const;
  void SetVelocity(const Vec2f& velocity);
  void SetPosition(const Vec2f& position);
  void SetHitPoints(double hit_points_);
  void SetBulletsAmount(double bullets_amount_);
  void SetMinesAmount(double mines_amount_);

  void SetFlagUp(bool flag_up);
  void SetFlagDown(bool flag_down);
  void SetFlagLeft(bool flag_left);
  void SetFlagRight(bool flag_right);
  bool IsShooting() const;
  void SetIsShooting(bool is_shooting);
  bool IsAlive() const;
  void SetIsAlive(bool is_alive);

 private:
  std::vector<Wheel> wheels_{4};
  Vec2f position_;
  Vec2f angle_vec_;
  Vec2f velocity_;

  double angular_velocity_ = 0;
  double steering_angle_ = 0;
  static constexpr double kAccelFactor = 2.0;
  static constexpr double kFrictionFactor = 0.5;
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
  static constexpr double kMinVelocityThreshold = 5;
  static constexpr double kMinAngularVelocityThreshold = 0.1;

  bool flag_up_ = false;
  bool flag_down_ = false;
  bool flag_left_ = false;
  bool flag_right_ = false;
  bool is_shooting_ = false;
  bool is_alive_ = true;

  double hit_points = 100;
  size_t bullets_amount_ = 1000;
  size_t mines_amount = 20;

 private:
  void UpdateWheelsPosAndOrientation();
  void AdvanceStep(int time_millisec);
  void CalcAccelerations(Vec2f* accel, double* angular_accel);
  void ProceedInputFlags();
  void CalcLateralForces();
};
