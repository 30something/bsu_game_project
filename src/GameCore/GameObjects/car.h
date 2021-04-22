//  Kindly taken from https://github.com/abainbridge/car_sim
#pragma once

#include <vector>
#include <algorithm>
#include <cmath>
#include <utility>
#include <optional>

#include <QPoint>

#include "src/helpers/vec2f.h"
#include "wheel.h"
#include "src/helpers/line.h"
#include "src/helpers/physics.h"
#include "game_object.h"
#include "src/GameCore/Behaviors/behavior.h"

class Car : public GameObject {
 public:
  Car(QPoint position,
      double angle,
      Behavior* behavior);
  ~Car() = default;

  void Tick(int time_millisec);

  std::optional<Vec2f> DropMine();
  std::optional<Line> ShootBullet();

  double GetHitPoints() const;
  double GetBulletsAmount() const;
  double GetMinesAmount() const;
  double GetAngle() const override;
  std::vector<Line> GetCollisionLines() const override;
  const Vec2f& GetVelocity() const;
  PixmapID GetPixmapId() const override;
  const Vec2f& GetAngleVec() const;
  bool IsPuttingMine() const;
  bool IsShooting() const;
  bool IsAlive() const;
  void SetVelocity(const Vec2f& velocity);
  void SetPosition(const Vec2f& position);
  void AddHitPoints(double hit_points_);
  void AddBulletsAmount(double bullets_amount_);
  void AddMinesAmount(double mines_amount_);
  void EnableInput(bool flag);
  void SetIsAlive(bool is_alive);

 private:
  std::vector<Wheel> wheels_{4};
  Behavior* behavior_ = nullptr;
  Vec2f angle_vec_;
  Vec2f velocity_;

  double angular_velocity_ = 0;
  double steering_angle_ = 0;
  static constexpr int kPutMineOffset = -15;
  static constexpr double kShootingRange = 100;
  static constexpr double kAccelFactor = 2.0;
  static constexpr double kFrictionFactor = 0.5;
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
  static constexpr double kMineDelayTicks = 500;

  bool is_alive_ = true;

  double hit_points_ = 200;
  size_t bullets_amount_ = 1000;
  size_t mines_amount_ = 5;
  size_t mines_tick_timer_ = 0;

  void UpdateWheelsPosAndOrientation();
  void AdvanceStep(int time_millisec);
  void CalcAccelerations(Vec2f* accel, double* angular_accel);
  void ProceedInputFlags();
  void CalcLateralForces();
};
