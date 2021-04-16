#include "game_object.h"

std::vector<Line> GameObject::GetCollisionLines() const {
  return std::vector<Line>();
}

double GameObject::GetAngle() const {
  return 0;
}

Vec2f GameObject::GetPosition() const {
  return position_;
}

GameObject::GameObject(const Vec2f& position) : position_(position) {}
