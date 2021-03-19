//  Kindly taken from https://github.com/abainbridge/car_sim
#pragma once

#include <vector>
#include <algorithm>
#include <cmath>
#include <utility>

#include "src/helpers/vec2f.h"
#include "wheel.h"
#include "src/helpers/line.h"
#include "car_physics.h"

class Car : public CarPhysics {
 public:
  Car(int x,
      int y,
      double angle,
      std::vector<std::vector<std::pair<int, int>>>* borders);
  ~Car() = default;

  void Tick(int time_millisec) override;

  void SetFlagUp(bool flag_up);
  void SetFlagDown(bool flag_down);
  void SetFlagLeft(bool flag_left);
  void SetFlagRight(bool flag_right);

 private:
  bool flag_up_ = false;
  bool flag_down_ = false;
  bool flag_left_ = false;
  bool flag_right_ = false;

  void ProceedInputFlags();
};
