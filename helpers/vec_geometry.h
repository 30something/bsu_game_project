#pragma once

#include <cmath>

class Vec2f {
 public:
  Vec2f() = default;
  Vec2f(double length, double angle);

  double GetX() const;
  double GetY() const;
  double GetAngle() const;
  double GetLength() const;

  void SetAngle(double angle);
  void SetLength(double length);
  void SetXY(double x, double y);
  void RotateCCW(double degrees);
  Vec2f operator+(const Vec2f& vec) const;

 private:
  static double FindAngleFromXY(double x, double y);
  static double FindLengthFromXY(double x, double y);
  double angle_ = 0;  // From right ccw
  double length_ = 0;
};
