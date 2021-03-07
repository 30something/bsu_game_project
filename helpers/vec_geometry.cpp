#include "vec_geometry.h"

double Vec2f::GetLength() const {
  return length_;
}

void Vec2f::RotateCCW(double degrees) {
  angle_ += degrees;
}

Vec2f::Vec2f(double length, double angle) :
    angle_(angle),
    length_(length) {
}

Vec2f Vec2f::operator+(const Vec2f& vec) const {
  double x = GetX() + vec.GetX();
  double y = GetY() + vec.GetY();
  return Vec2f(FindLengthFromXY(x, y), FindAngleFromXY(x, y));
}

void Vec2f::SetLength(double length) {
  length_ = length;
}

double Vec2f::GetY() const {
  return length_ * cos(angle_ * 2 * M_PI / 360.);
}

double Vec2f::GetX() const {
  return length_ * sin(angle_ * 2 * M_PI / 360.);
}

double Vec2f::FindAngleFromXY(double x, double y) {
  if (x < 0.00001 && y < 0.00001) {
    return 0;
  }
  double angle = std::abs(atan(y / x) * 360 / 2 / M_PI);
  if (x >= 0 && y <= 0) {
    angle += 270;
  } else if (x <= 0 && y >= 0) {
    angle += 90;
  } else {
    angle += 180;
  }
  return angle;
}

double Vec2f::GetAngle() const {
  return angle_;
}

void Vec2f::SetAngle(double angle) {
  angle_ = angle;
}

double Vec2f::FindLengthFromXY(double x, double y) {
  return sqrt(x * x + y * y);
}

void Vec2f::SetXY(double x, double y) {
  this->SetAngle(FindAngleFromXY(x, y));
  this->SetLength(FindLengthFromXY(x, y));
}
