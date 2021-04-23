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

std::vector<Line> Mine::GetCollisionLines() const {
  Vec2f p1(position_.GetX() - kMineRange, position_.GetY() - kMineRange);
  Vec2f p2(position_.GetX() + kMineRange, position_.GetY() - kMineRange);
  Vec2f p3(position_.GetX() + kMineRange, position_.GetY() + kMineRange);
  Vec2f p4(position_.GetX() - kMineRange, position_.GetY() + kMineRange);
  Line l1(p1, p2);
  Line l2(p2, p3);
  Line l3(p3, p4);
  Line l4(p4, p1);
  return {l1, l2, l3, l4};
}

void Mine::SetIsExploded(bool is_exploded) {
  is_exploded_ = is_exploded;
}

bool Mine::IsExploded() const {
  return is_exploded_;
}
