#pragma once

#include <vector>

#include <QPoint>
#include <QRandomGenerator>

#include "line.h"

class Physics {
 public:
  static constexpr double kAlmostZero = 0.000001;
  static constexpr double kCollisionDeviationScalar = 40.0;

  static bool IsInside(const std::vector<Line>& rect, const QPoint& point);
  static bool IsIntersects(Line l1, Line l2);
  static Vec2f FindIntersectionPoint(Line l1, Line l2);
  static bool IsIntersects(const std::vector<Line>& lines_1,
                           const std::vector<Line>& lines_2);
  static int Product(const QPoint& m, const QPoint& p1, const QPoint& p2);
  static double Distance(QPoint first, QPoint second);
  static QPoint GetRandomPointOnLine(Line line);
};
