#pragma once

#include <vector>

#include <QPoint>
#include <QRandomGenerator>

#include "line.h"

namespace physics {

constexpr double kAlmostZero = 0.000001;
constexpr double kCollisionDeviationScalar = 40.0;

bool IsIntersects(Line l1, Line l2);
Vec2f FindIntersectionPoint(Line l1, Line l2);
bool IsIntersects(const std::vector<Line>& lines_1,
                  const std::vector<Line>& lines_2);
double Distance(Vec2f first, Vec2f second);
double CalculateLineDeviation(double x_pos, double y_pos, Line line);
Vec2f GetRandomPointOnLine(Line line, double lower, double upper);

}  // namespace physics
