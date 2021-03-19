#include "line.h"


bool Line::IsIntersects(Line l1, Line l2) {
  // Code taken somewhere from the internet with smol bug fix
  double ax1 = l1.x1;
  double ay1 = l1.y1;
  double ax2 = l1.x2;
  double ay2 = l1.y2;
  double bx1 = l2.x1;
  double by1 = l2.y1;
  double bx2 = l2.x2;
  double by2 = l2.y2;
  double v1 = (bx2 - bx1) * (ay1 - by1) - (by2 - by1) * (ax1 - bx1);
  double v2 = (bx2 - bx1) * (ay2 - by1) - (by2 - by1) * (ax2 - bx1);
  double v3 = (ax2 - ax1) * (by1 - ay1) - (ay2 - ay1) * (bx1 - ax1);
  double v4 = (ax2 - ax1) * (by2 - ay1) - (ay2 - ay1) * (bx2 - ax1);
  bool left;
  bool right;
  if ((v1 < 0 && v2 < 0) || (v1 > 0 && v2 > 0)) {
    left = false;
  } else if ((v1 < 0 && v2 > 0) || (v1 > 0 && v2 < 0)) {
    left = true;
  } else {
    left = false;
  }

  if ((v3 < 0 && v4 < 0) || (v3 > 0 && v4 > 0)) {
    right = false;
  } else if ((v3 < 0 && v4 > 0) || (v3 > 0 && v4 < 0)) {
    right = true;
  } else {
    right = false;
  }

  return left && right;
}
