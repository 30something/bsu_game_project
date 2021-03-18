//  https://github.com/abainbridge/car_sim
#pragma once

#include <cmath>

struct Line {
  Line(double x1_, double y1_, double x2_, double y2_) :
      x1(x1_),
      y1(y1_),
      x2(x2_),
      y2(y2_) {};
  Line() = default;
  double x1 = 0;
  double y1 = 0;
  double x2 = 0;
  double y2 = 0;
};

class Vec2f {
 private:
  double x_;
  double y_;

 public:
  double GetX() const;
  void SetX(double _x);
  double GetY() const;
  void SetY(double _y);

 public:
  Vec2f() : x_(0.0), y_(0.0) {
  }

  Vec2f(double _x, double _y) : x_(_x), y_(_y) {
  }

  void Set(double _x, double _y);

  Vec2f operator+(const Vec2f& b) const;

  Vec2f operator-(const Vec2f& b) const;

  Vec2f operator*(double b) const;

  Vec2f& operator=(const Vec2f& b) = default;

  Vec2f& operator*=(double b);

  Vec2f& operator+=(const Vec2f& b);

  Vec2f& operator-=(const Vec2f& b);

  Vec2f& operator/=(const Vec2f& b);

  Vec2f const& Normalize();
  void SetLen(double len);
  void Rotate(double radians);
  double AngleBetween(const Vec2f& other);

  Vec2f GetPerpendicular() const;
  double GetLength() const;
  double GetAngleDegrees() const;
};
