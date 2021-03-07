//  https://github.com/abainbridge/car_sim
#pragma once

#include <cmath>

class Vec2f {
 public:
  double x, y;

  Vec2f() {
    x = 0.0;
    y = 0.0;
  }

  Vec2f(double _x, double _y) {
    x = _x;
    y = _y;
  }

  void Set(double _x, double _y) {
    x = _x;
    y = _y;
  }

  Vec2f operator+(Vec2f const& b) const;

  Vec2f operator-(Vec2f const& b) const;

  Vec2f operator*(double b) const;

  Vec2f& operator=(Vec2f const& b) = default;

  void operator*=(double const b) {
    x *= b;
    y *= b;
  }

  void operator+=(Vec2f const& b) {
    x += b.x;
    y += b.y;
  }

  void operator-=(Vec2f const& b) {
    x -= b.x;
    y -= b.y;
  }

  Vec2f const& Normalize();
  void SetLen(double len);
  void Rotate(double radians);
  double AngleBetween(Vec2f const& other);

  Vec2f GetPerpendicular() const;
  double GetLength() const;
  double GetAngleDegrees() const;
};
