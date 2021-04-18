#pragma once

#include <cstdint>

struct CarAchievements {
  int32_t laps_counter = 0;
  double finish_deviation = 0;
  double current_showed_velocity = 0;
  bool is_collide_with_finish = false;
};
