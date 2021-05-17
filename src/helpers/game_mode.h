#pragma once

#include "src/Network/network_controller.h"

struct GameMode {
  uint32_t map_index = 0;
  uint32_t players_amount = 1;
  uint32_t network_players_amount = 0;
  uint32_t bots_amount = 0;
  int32_t laps_amount = 1;
  int32_t first_player_car_number = 0;
  int32_t second_player_car_number = 0;
  bool enable_drifting = false;
  NetworkController* network_controller = nullptr;
};
