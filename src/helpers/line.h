#pragma once

#include "vec2f.h"

struct Line {
  Line(double x1_, double y1_, double x2_, double y2_) :
      x1(x1_),
      y1(y1_),
      x2(x2_),
      y2(y2_) {}
  Line(Vec2f first, Vec2f second) :
  x1(first.GetX()),
  y1(first.GetY()),
  x2(second.GetX()),
  y2(second.GetY()) {}
  Line() = default;
  double x1 = 0;
  double y1 = 0;
  double x2 = 0;
  double y2 = 0;
  static bool IsIntersects(Line l1, Line l2);
  static Vec2f FindIntersectionPoint(Line l1, Line l2);
};
