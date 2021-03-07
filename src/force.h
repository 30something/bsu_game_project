#pragma once

#include "helpers/vec_geometry.h"

struct Force {
  Force(int x, int y, Vec2f force_vec);
  int x = 0;
  int y = 0;
  Vec2f force_vector_{0.0, 0.0};
};

