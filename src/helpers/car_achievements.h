#pragma once

#include <cstdint>

struct CarAchievements {
  size_t laps_counter = 0;
  size_t finish_position = 0;
  size_t current_order_position = 0;
  size_t car_number = 0;
  size_t bullets_amount_ = 1000;
  size_t mines_amount_ = 10;
  size_t elapsed_millis_time = 0;
  double hit_points_ = 200;
  double finish_deviation = 0;
  double current_showed_velocity = 0;
  double launched_finish_deviation = 0;
  bool is_collide_with_finish = false;
  bool animation_of_death_state = false;
  bool animation_of_shooting_state = false;
  bool is_finished = false;
};
