#include "mine.h"

Mine::Mine(Vec2f position) : position_(position) {}

Vec2f Mine::GetPosition() const {
  return position_;
}

PixmapID Mine::GetPixmapId() const {
  return PixmapID::kMine;
}

bool Mine::operator==(const Mine& rhs) const {
  return position_ == rhs.position_;
}

bool Mine::operator!=(const Mine& rhs) const {
  return !(rhs == *this);
}