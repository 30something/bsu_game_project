#include "physics.h"

int physics::Product(const QPoint& m, const QPoint& p1, const QPoint& p2) {
  return (p2.x() - p1.x()) * (m.y() - p1.y())
      - (p2.y() - p1.y()) * (m.x() - p1.x());
}

//  Works only with rectangles
bool physics::IsInside(const std::vector<Line>& rect, const QPoint& point) {
  int p1 = Product(point,
                   QPoint(rect[0].x1, rect[0].y1),
                   QPoint(rect[0].x2, rect[0].y2));
  int p2 = Product(point,
                   QPoint(rect[0].x2, rect[0].y2),
                   QPoint(rect[1].x2, rect[1].y2));
  int p3 = Product(point,
                   QPoint(rect[1].x2, rect[1].y2),
                   QPoint(rect[2].x2, rect[2].y2));
  int p4 = Product(point,
                   QPoint(rect[2].x2, rect[2].y2),
                   QPoint(rect[0].x1, rect[0].y1));
  return ((p1 < 0 && p2 < 0 && p3 < 0 && p4 < 0) ||
      (p1 > 0 && p2 > 0 && p3 > 0 && p4 > 0));
}

bool physics::IsIntersects(Line l1, Line l2) {
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

Vec2f physics::FindIntersectionPoint(Line l1, Line l2) {
  if (l1.x1 - l1.x2 == 0) {
    l1.x2 += physics::kAlmostZero;
  }
  if (l2.x1 - l2.x2 == 0) {
    l2.x2 += physics::kAlmostZero;
  }
  double k1 = (l1.y1 - l1.y2) / (l1.x1 - l1.x2);
  double k2 = (l2.y1 - l2.y2) / (l2.x1 - l2.x2);
  double b1 = l1.y1 - k1 * l1.x1;
  double b2 = l2.y1 - k2 * l2.x1;
  double result_x = (b2 - b1) / (k1 - k2);
  double result_y = k1 * result_x + b1;
  return Vec2f(result_x, result_y);
}

bool physics::IsIntersects(const std::vector<Line>& lines_1,
                           const std::vector<Line>& lines_2) {
  for (const auto& line1 : lines_1) {
    for (const auto& line2 : lines_2) {
      if (IsIntersects(line1, line2)) {
        return true;
      }
    }
  }
  return false;
}

double physics::Distance(QPoint first, QPoint second) {
  return std::hypot(first.x() - second.x(), first.y() - second.y());
}

double physics::CalculateLineDeviation(double x_pos, double y_pos, Line line) {
  // Using general form of line equation
  double A = line.y1 - line.y2;
  double B = line.x2 - line.x1;
  double C = line.x1 * line.y2 - line.x2 * line.y1;
  double d = (A * x_pos + B * y_pos + C) / sqrt(A * A + B * B);
  if (C > 0) {
    d *= -1;
  }
  return d;
}

Vec2f physics::GetRandomPointOnLine(Line line, double lower, double upper) {
  double dx = line.x1 - line.x2;
  double dy = line.y1 - line.y2;
  double scalar = QRandomGenerator::global()->generateDouble();
  if(scalar < lower) {
    scalar = lower;
  }
  if(scalar > upper) {
    scalar = upper;
  }
  dx *= scalar;
  dy *= scalar;
  return Vec2f(line.x1 - dx, line.y1 - dy);
}
