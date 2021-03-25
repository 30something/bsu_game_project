#pragma once

#include "vec2f.h"

struct Line {
  Line(double x1_, double y1_, double x2_, double y2_) :
      x1(x1_),
      y1(y1_),
      x2(x2_),
      y2(y2_) {}

  Line() = default;
  double x1 = 0;
  double y1 = 0;
  double x2 = 0;
  double y2 = 0;
  static bool IsIntersects(Line l1, Line l2);
};
