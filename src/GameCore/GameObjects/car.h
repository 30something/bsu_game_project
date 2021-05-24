//  Kindly taken from https://github.com/abainbridge/car_sim
#pragma once

#include <algorithm>
#include <cmath>
#include <memory>
#include <utility>
#include <optional>
#include <vector>

#include <QPoint>

#include "src/helpers/vec2f.h"
#include "wheel.h"
#include "src/helpers/line.h"
#include "src/helpers/physics.h"
#include "src/helpers/cars_colors.h"
#include "src/helpers/animations_info.h"
#include "game_object.h"
#include "src/GameCore/Behaviors/behavior.h"
#include "src/GameCore/GameObjects/animation.h"

class Car : public GameObject {
 public:
  Car(Vec2f position,
      double angle,
      Behavior* behavior,
      CarsColors car_color,
      bool enable_drifts);
  ~Car() override = default;

  void Tick(int time_millisec);

  std::optional<Vec2f> DropMine();
  std::optional<Line> ShootBullet();

  double GetHitPoints() const;
  size_t GetBulletsAmount() const;
  size_t GetMinesAmount() const;
  size_t GetColor() const;
  double GetAngle() const override;
  const std::vector<Line>& GetCollisionLines() const override;
  const Vec2f& GetVelocity() const;
  const Vec2f& GetAngleVec() const;
  const Vec2f* GetAngleVecPointer() const;
  bool IsPuttingMine() const;
  bool IsShooting() const;
  void SetAngleVec(const Vec2f& angle_vec);
  void SetVelocity(const Vec2f& velocity);
  void SetPosition(const Vec2f& position);
  void AddHitPoints(double hit_points_);
  void AddBulletsAmount(size_t bullets_amount_);
  void AddMinesAmount(size_t mines_amount_);
  void EnableInput(bool flag);
  void BecomeDead();

 private:
  class CarPixmapComponent : public PixmapComponent {
   public:
    void SetCarPixmapId(CarStates car_state, CarsColors car_color);
    ~CarPixmapComponent() override = default;
    size_t GetFramesForChangingHitpoints() const;
    bool GetShowingHealthChangeState() const;
    void SetFramesForChangingHitPoints(size_t frames_for_changing_hitpoints);
    void SetShowingHealthChangeState(bool showing_health_change_state);
    void DecrementFramesForChangingHitpoints();

    static constexpr size_t kChangingHitPointsAnimationLastFrame = 40;

   private:
    size_t frames_for_changing_hitpoints_ =
        kChangingHitPointsAnimationLastFrame;
    bool showing_health_change_state_ = false;
  };

  void UpdateWheelsPosAndOrientation();
  void RealisticStep(int time_millisec);
  void ArcadeStep(int time_millisec);
  void CalcAccelerations(Vec2f* accel, double* angular_accel);
  void ProceedInputFlagsRealistic();
  void ProceedInputFlagsArcade();
  void CalcLateralForces();
  void ProceedUpDownFlags();
  void UpdateCollisionLines() override;
  void ChoosePixmap();

  static constexpr int32_t kPutMineOffset = -15;
  static constexpr int32_t kMineDelayTicks = 500;
  static constexpr double kShootingRange = 300;
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
  static constexpr double kTickRotationAngle = 0.015;
  static constexpr double kMinSignificantDamage = 0.3;

  std::vector<Wheel> wheels_{4};
  std::shared_ptr<Behavior> behavior_ = nullptr;
  Vec2f angle_vec_;
  Vec2f velocity_;
  CarsColors car_color_;
  CarPixmapComponent* car_pixmap_component_ = nullptr;
  double hit_points_ = 200;
  size_t bullets_amount_ = 1000;
  size_t mines_amount_ = 10;
  size_t mines_tick_timer_ = 0;
  double angular_velocity_ = 0;
  double steering_angle_ = 0;
  bool enable_drifts_ = true;
  bool health_increasing_state = false;
};
