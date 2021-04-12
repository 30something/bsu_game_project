#include "mine.h"

Mine::Mine(Vec2f position) : position_(position) {}

const Vec2f& Mine::GetPosition() const {
  return position_;
}

double Mine::GetAngle() const {
  return 0;
}

std::string Mine::GetPixmapId() const {
  return std::string("mine");
}

std::vector<Line> Mine::GetLines() const {
  return std::vector<Line>();
}

bool Mine::operator==(const Mine& rhs) const {
  return position_ == rhs.position_;
}

bool Mine::operator!=(const Mine& rhs) const {
  return !(rhs == *this);
}
