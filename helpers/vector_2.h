#pragma once

class Vector2 {
 public:
  double x, y;

  Vector2() { x = y = 0.0; }
  Vector2(double _x, double _y) {
    x = _x;
    y = _y;
  }

  void Set(double _x, double _y) {
    x = _x;
    y = _y;
  }

  Vector2 operator+(Vector2 const& b) const;
  Vector2 operator-(Vector2 const& b) const;
  Vector2 operator*(double const b) const;

  void operator=(Vector2 const& b) {
    x = b.x;
    y = b.y;
  }
  void operator*=(double const b) {
    x *= b;
    y *= b;
  }
  void operator+=(Vector2 const& b) {
    x += b.x;
    y += b.y;
  }
  void operator-=(Vector2 const& b) {
    x -= b.x;
    y -= b.y;
  }

  Vector2 const& Normalize();
  void SetLen(double len);

  void Rotate(double radians);
  double AngleBetween(Vector2 const& other);
  Vector2 GetPerpendicular() const;

  double GetLength() const;
  double GetAngleDegrees() const;
};
