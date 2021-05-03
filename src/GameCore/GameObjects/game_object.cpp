#include "game_object.h"

GameObject::GameObject(const Vec2f& position,
                       PixmapComponent* pixmap_component) :
    position_(position),
    collision_lines_(4),
    pixmap_component_(pixmap_component) {
  UpdateCollisionLines();
}

GameObject::~GameObject() {
  delete pixmap_component_;
}

const std::vector<Line>& GameObject::GetCollisionLines() const {
  return collision_lines_;
}

double GameObject::GetAngle() const {
  return 0;
}

Vec2f GameObject::GetPosition() const {
  return position_;
}

void GameObject::UpdateCollisionLines() {
  Vec2f p1(position_.GetX() - kDefaultSize, position_.GetY() - kDefaultSize);
  Vec2f p2(position_.GetX() + kDefaultSize, position_.GetY() - kDefaultSize);
  Vec2f p3(position_.GetX() + kDefaultSize, position_.GetY() + kDefaultSize);
  Vec2f p4(position_.GetX() - kDefaultSize, position_.GetY() + kDefaultSize);
  collision_lines_[0] = Line(p1, p2);
  collision_lines_[1] = Line(p2, p3);
  collision_lines_[2] = Line(p3, p4);
  collision_lines_[3] = Line(p4, p1);
}

PixmapID GameObject::GetPixmapId() const {
  return pixmap_component_->GetPixmapId();
}

PixmapID GameObject::PixmapComponent::GetPixmapId() const {
  return pixmap_id_;
}
