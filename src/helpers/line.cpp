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
