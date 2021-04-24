#include "game_object.h"

std::vector<Line> GameObject::GetCollisionLines() const {
  Vec2f p1(position_.GetX() - kDefaultSize, position_.GetY() - kDefaultSize);
  Vec2f p2(position_.GetX() + kDefaultSize, position_.GetY() - kDefaultSize);
  Vec2f p3(position_.GetX() + kDefaultSize, position_.GetY() + kDefaultSize);
  Vec2f p4(position_.GetX() - kDefaultSize, position_.GetY() + kDefaultSize);
  Line l1(p1, p2);
  Line l2(p2, p3);
  Line l3(p3, p4);
  Line l4(p4, p1);
  return {l1, l2, l3, l4};
}

double GameObject::GetAngle() const {
  return 0;
}

Vec2f GameObject::GetPosition() const {
  return position_;
}

GameObject::GameObject(const Vec2f& position) : position_(position) {}
