#pragma once

#include <vector>

#include "src/helpers/car_achievements.h"

struct CarsData {
  explicit CarsData(uint32_t players_amount);

  void UpdateCarsData(const std::vector<CarAchievements>& new_cars_data);

  double GetVelocity(int index) const;
  int32_t GetLapsCounter(int index) const;

  std::vector<CarAchievements> cars_data;
  static constexpr double kMinVisibleVelocity = 5;
};
