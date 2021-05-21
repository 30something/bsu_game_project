#pragma once

#include <algorithm>
#include <vector>
#include <utility>

#include "src/helpers/car_achievements.h"

struct CarsData {
  CarsData() = default;
  explicit CarsData(std::vector<CarAchievements>  new_cars_data);

  double GetVelocity(int index) const;
  int32_t GetLapsCounter(int index) const;
  size_t GetBulletsAmount(int index) const;
  size_t GetMinesAmount(int index) const;
  double GetHP(int index) const;
  size_t GetElapsedTime(int index) const;
  int32_t GetFinishPosition(int index) const;
  uint32_t GetCurrentOrderPosition(int index) const;

  std::vector<CarAchievements> cars_data;
  static constexpr double kMinVisibleVelocity = 5;
};
