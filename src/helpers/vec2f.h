//  https://github.com/abainbridge/car_sim
#pragma once

#include <cmath>

class Vec2f {
 public:
  double x;
  double y;

  Vec2f() {
    x = 0.0;
    y = 0.0;
  }

  Vec2f(double _x, double _y) : x(_x), y(_y) {
  }

  void Set(double _x, double _y) {
    x = _x;
    y = _y;
  }

  Vec2f operator+(const Vec2f& b) const;

  Vec2f operator-(const Vec2f& b) const;

  Vec2f operator*(double b) const;

  Vec2f& operator=(const Vec2f& b) = default;

  void operator*=(double b) {
    x *= b;
    y *= b;
  }

  void operator+=(const Vec2f& b) {
    x += b.x;
    y += b.y;
  }

  void operator-=(const Vec2f& b) {
    x -= b.x;
    y -= b.y;
  }

  Vec2f const& Normalize();
  void SetLen(double len);
  void Rotate(double radians);
  double AngleBetween(const Vec2f& other);

  Vec2f GetPerpendicular() const;
  double GetLength() const;
  double GetAngleDegrees() const;
};
