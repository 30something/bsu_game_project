#pragma once

struct GameMode {
  uint32_t map_index = 0;
  uint32_t players_amount = 1;
  uint32_t bots_amount = 0;
  int32_t laps_amount = 1;
};
