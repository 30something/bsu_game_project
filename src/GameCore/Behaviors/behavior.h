#pragma once

#include "src/GameCore/GameObjects/game_object.h"

class Behavior {
 public:
  virtual void HandleTick(const GameObject*) = 0;

  bool IsFlagUp() const;
  bool IsFlagDown() const;
  bool IsFlagLeft() const;
  bool IsFlagRight() const;
  bool IsFlagShoot() const;
  bool IsFlagMine() const;

 protected:
  bool flag_up_ = false;
  bool flag_down_ = false;
  bool flag_left_ = false;
  bool flag_right_ = false;
  bool flag_shoot_ = false;
  bool flag_mine_ = false;
};
