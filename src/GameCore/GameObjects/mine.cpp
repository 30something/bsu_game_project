#include "mine.h"

Mine::Mine(Vec2f position) : GameObject(position) {}

PixmapID Mine::GetPixmapId() const {
  return is_exploded_ ? PixmapID::kExplodedMine : PixmapID::kMine;
}

bool Mine::operator==(const Mine& rhs) const {
  return position_ == rhs.position_;
}

bool Mine::operator!=(const Mine& rhs) const {
  return !(rhs == *this);
}

void Mine::SetIsExploded(bool is_exploded) {
  is_exploded_ = is_exploded;
}

bool Mine::IsExploded() const {
  return is_exploded_;
}
