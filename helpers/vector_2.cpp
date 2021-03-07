//  https://github.com/abainbridge/car_sim
#include "vector_2.h"

#include <math.h>

Vector2 Vector2::operator+(Vector2 const& b) const {
  return Vector2(x + b.x, y + b.y);
}

Vector2 Vector2::operator-(Vector2 const& b) const {
  return Vector2(x - b.x, y - b.y);
}

Vector2 Vector2::operator*(double const b) const {
  return Vector2(x * b, y * b);
}

Vector2 const& Vector2::Normalize() {
  double length_squared = x * x + y * y;
  if (length_squared > 0.0f) {
    double inverted_length = 1.0f / sqrtf(length_squared);
    x *= inverted_length;
    y *= inverted_length;
  } else {
    x = 0.0f;
    y = 1.0f;
  }

  return *this;
}

void Vector2::SetLen(double len) {
  double scaler = len / GetLength();
  x *= scaler;
  y *= scaler;
}

void Vector2::Rotate(double radians) {
  double tmp = x;
  double cs = cos(radians);
  double sn = sin(radians);
  x = x * cs - y * sn;
  y = tmp * sn + y * cs;
}

double Vector2::AngleBetween(Vector2 const& other) {
  Vector2 this_normalized = *this;
  this_normalized.Normalize();
  Vector2 other_normalized = other;
  other_normalized.Normalize();
  return this_normalized.y * other_normalized.x
      - this_normalized.x * other_normalized.y;
}

Vector2 Vector2::GetPerpendicular() const {
  return Vector2(y, -x);
}

double Vector2::GetLength() const {
  return sqrtf(x * x + y * y);
}
double Vector2::GetAngleDegrees() const {
  double angle = atan(y / x) * 360 / 2 / M_PI;
  if (x < 0) {
    angle += 180;
  }
  return angle;
}
