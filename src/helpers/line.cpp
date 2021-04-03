#include "line.h"

bool Line::IsIntersects(Line l1, Line l2) {
  // Code taken somewhere from the internet with smol bug fix
  double v1 =
      (l2.x2 - l2.x1) * (l1.y1 - l2.y1) - (l2.y2 - l2.y1) * (l1.x1 - l2.x1);
  double v2 =
      (l2.x2 - l2.x1) * (l1.y2 - l2.y1) - (l2.y2 - l2.y1) * (l1.x2 - l2.x1);
  double v3 =
      (l1.x2 - l1.x1) * (l2.y1 - l1.y1) - (l1.y2 - l1.y1) * (l2.x1 - l1.x1);
  double v4 =
      (l1.x2 - l1.x1) * (l2.y2 - l1.y1) - (l1.y2 - l1.y1) * (l2.x2 - l1.x1);
  bool left = false;
  bool right = false;

  if ((v1 < 0 && v2 > 0) || (v1 > 0 && v2 < 0)) {
    left = true;
  }
  if ((v3 < 0 && v4 > 0) || (v3 > 0 && v4 < 0)) {
    right = true;
  }
  return left && right;
}

Vec2f Line::FindIntersectionPoint(Line l1, Line l2) {
  double k1 = (l1.y1 - l1.y2) / (l1.x1 - l1.x2);
  double k2 = (l2.y1 - l2.y2) / (l2.x1 - l2.x2);
  double b1 = l1.y1 - k1 * l1.x1;
  double b2 = l2.y1 - k2 * l2.x1;
  double result_x = (b2 - b1) / (k1 - k2);
  double result_y = k1 * result_x + b1;
  return Vec2f(result_x, result_y);
}
