#include "vec_geometry.h"

double Vec2f::GetLength() const {
  return length_;
}

void Vec2f::RotateCCW(double degrees) {
  angle_ += degrees;
}

Vec2f::Vec2f(double x, double y) {
  angle_ = FindAngleFromXY(x, y);
  length_ = sqrt(x * x + y * y);
}

Vec2f Vec2f::operator+(const Vec2f& vec) const {
  return Vec2f(GetX() + vec.GetX(), GetY() + vec.GetY());
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
  angle_ = std::abs(atan(y / x) * 360 / 2 / M_PI);
  if (x >= 0 && y <= 0) {
    angle_ += 270;
  } else if (x <= 0 && y >= 0) {
    angle_ += 90;
  } else {
    angle_ += 180;
  }
  return angle_;
}
double Vec2f::GetAngle() const {
  return angle_;
}
void Vec2f::SetAngle(double angle) {
  angle_ = angle;
}
