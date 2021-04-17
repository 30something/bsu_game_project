#pragma once

#include <vector>

#include <QPoint>
#include <QRandomGenerator>

#include "line.h"

namespace physics {
  constexpr double kAlmostZero = 0.000001;
  constexpr double kCollisionDeviationScalar = 40.0;

  bool IsInside(const std::vector<Line>& rect, const QPoint& point);
  bool IsIntersects(Line l1, Line l2);
  Vec2f FindIntersectionPoint(Line l1, Line l2);
  bool IsIntersects(const std::vector<Line>& lines_1,
                    const std::vector<Line>& lines_2);
  int Product(const QPoint& m, const QPoint& p1, const QPoint& p2);
  double Distance(QPoint first, QPoint second);
  Vec2f GetRandomPointOnLine(Line line);

}  // namespace physics
