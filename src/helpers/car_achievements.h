#pragma once

#include <cstdint>

struct CarAchievements {
  int32_t laps_counter = 0;
  int32_t finish_position = INT32_MAX;
  size_t bullets_amount_ = 1000;
  size_t mines_amount_ = 10;
  size_t elapsed_millis_time = 0;
  double hit_points_ = 200;
  double finish_deviation = 0;
  double current_showed_velocity = 0;
  double launched_finish_deviation = 0;
  bool is_collide_with_finish = false;
  bool is_finished = false;
};
