#pragma once

#include <cmath>

class Vec2f {
 public:
  Vec2f() = default;
  Vec2f(double x, double y);
  double GetX() const;
  double GetAngle() const;
  void SetAngle(double angle);
  void SetLength(double length);
  double GetLength() const;
  void RotateCCW(double degrees);
  Vec2f operator+(const Vec2f& vec) const;
  double GetY() const;

 private:
  double FindAngleFromXY(double x, double y);
  double angle_ = 0;  // From right ccw
  double length_ = 0;
};
