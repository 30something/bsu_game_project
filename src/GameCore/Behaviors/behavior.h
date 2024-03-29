#pragma once

#include "src/GameCore/GameObjects/game_object.h"

class Behavior {
 public:
  virtual void HandleTick(GameObject*) = 0;
  virtual ~Behavior() = default;

  bool IsFlagUp() const;
  bool IsFlagDown() const;
  bool IsFlagLeft() const;
  bool IsFlagRight() const;
  bool IsFlagShoot() const;
  bool IsFlagMine() const;

  bool IsDead() const;
  void SetIsDead();

  double GetMaxSpeed() const;
  void EnableInput(bool enable);

 protected:
  static constexpr double kMaxSpeed = 240;
  double max_speed_ = kMaxSpeed;
  bool enable_input_ = true;
  bool is_dead_ = false;
  bool flag_up_ = false;
  bool flag_down_ = false;
  bool flag_left_ = false;
  bool flag_right_ = false;
  bool flag_shoot_ = false;
  bool flag_mine_ = false;
};
