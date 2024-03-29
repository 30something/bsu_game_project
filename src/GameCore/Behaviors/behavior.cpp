#include "behavior.h"

bool Behavior::IsFlagUp() const {
  return flag_up_ && enable_input_;
}

bool Behavior::IsFlagDown() const {
  return flag_down_ && enable_input_;
}

bool Behavior::IsFlagLeft() const {
  return flag_left_ && enable_input_;
}

bool Behavior::IsFlagRight() const {
  return flag_right_ && enable_input_;
}

bool Behavior::IsFlagShoot() const {
  return flag_shoot_ && enable_input_;
}

bool Behavior::IsFlagMine() const {
  return flag_mine_ && enable_input_;
}

void Behavior::EnableInput(bool enable) {
  enable_input_ = enable;
}

double Behavior::GetMaxSpeed() const {
  return max_speed_;
}

bool Behavior::IsDead() const {
  return is_dead_;
}

void Behavior::SetIsDead() {
  is_dead_ = true;
}
