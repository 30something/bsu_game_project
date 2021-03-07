//  https://github.com/abainbridge/car_sim
#include "vec2f.h"



Vec2f Vec2f::operator+(Vec2f const& b) const {
  return Vec2f(x + b.x, y + b.y);
}

Vec2f Vec2f::operator-(Vec2f const& b) const {
  return Vec2f(x - b.x, y - b.y);
}

Vec2f Vec2f::operator*(double const b) const {
  return Vec2f(x * b, y * b);
}

Vec2f const& Vec2f::Normalize() {
  double length_squared = x * x + y * y;
  if (length_squared > 0.0f) {
    double inverted_length = 1.0f / sqrt(length_squared);
    x *= inverted_length;
    y *= inverted_length;
  } else {
    x = 0.0f;
    y = 1.0f;
  }

  return *this;
}

void Vec2f::SetLen(double len) {
  double scalar = len / GetLength();
  x *= scalar;
  y *= scalar;
}

void Vec2f::Rotate(double radians) {
  double tmp = x;
  double cs = cos(radians);
  double sn = sin(radians);
  x = x * cs - y * sn;
  y = tmp * sn + y * cs;
}

double Vec2f::AngleBetween(Vec2f const& other) {
  Vec2f this_normalized = *this;
  this_normalized.Normalize();
  Vec2f other_normalized = other;
  other_normalized.Normalize();
  return this_normalized.y * other_normalized.x
      - this_normalized.x * other_normalized.y;
}

Vec2f Vec2f::GetPerpendicular() const {
  return Vec2f(y, -x);
}

double Vec2f::GetLength() const {
  return sqrt(x * x + y * y);
}
double Vec2f::GetAngleDegrees() const {
  double angle = atan(y / x) * 360 / 2 / M_PI;
  if (x < 0) {
    angle += 180;
  }
  return angle;
}
