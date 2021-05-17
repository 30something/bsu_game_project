#pragma once

#include <vector>
#include <utility>

#include "src/helpers/car_achievements.h"

struct CarsData {
  CarsData() = default;
  explicit CarsData(std::vector<CarAchievements>  new_cars_data);

  double GetVelocity(int index) const;
  int32_t GetLapsCounter(int index) const;

  std::vector<CarAchievements> cars_data;
  static constexpr double kMinVisibleVelocity = 5;
};
