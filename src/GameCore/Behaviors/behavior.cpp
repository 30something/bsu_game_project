#include "behavior.h"

bool Behavior::IsFlagUp() const {
  return flag_up_;
}

bool Behavior::IsFlagDown() const {
  return flag_down_;
}

bool Behavior::IsFlagLeft() const {
  return flag_left_;
}

bool Behavior::IsFlagRight() const {
  return flag_right_;
}

bool Behavior::IsFlagShoot() const {
  return flag_shoot_;
}

bool Behavior::IsFlagMine() const {
  return flag_mine_;
}

double Behavior::GetMaxSpeed() const {
  return max_speed_;
}
