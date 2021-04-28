#include "mine.h"

Mine::Mine(Vec2f position) : GameObject(position) {
  pixmap_id_ = PixmapID::kMine;
}

bool Mine::operator==(const Mine& rhs) const {
  return position_ == rhs.position_;
}

bool Mine::operator!=(const Mine& rhs) const {
  return !(rhs == *this);
}

void Mine::SetExploaded() {
  pixmap_id_ = PixmapID::kExplodedMine;
  is_exploded_ = true;
}

bool Mine::IsExploaded() const {
  return is_exploded_;
}
