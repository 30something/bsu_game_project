#pragma once

#include "src/Network/network_controller.h"

struct GameMode {
  size_t map_index = 0;
  size_t players_amount = 1;
  size_t network_players_amount = 0;
  size_t bots_amount = 0;
  size_t laps_amount = 1;
  size_t first_player_car_number = 0;
  size_t second_player_car_number = 0;
  bool enable_drifting = false;
  NetworkController* network_controller = nullptr;
};
