#include "mine.h"

Mine::Mine(Vec2f position) :
  GameObject(position),
  pixmap_component_(new MinePixmapComponent) {
  pixmap_component_->SetMinePixmapId(MineStates::kStandard);
}

void Mine::MinePixmapComponent::SetMinePixmapId(MineStates mine_state) {
  auto category_value = static_cast<int32_t>(PixmapCategories::kMine);
  auto mine_state_value = static_cast<int32_t>(mine_state);
  pixmap_id_ = (category_value << 24) + (mine_state_value << 16);
}

bool Mine::operator==(const Mine& rhs) const {
  return position_ == rhs.position_;
}

bool Mine::operator!=(const Mine& rhs) const {
  return !(rhs == *this);
}

void Mine::SetExploded() {
  pixmap_component_->SetMinePixmapId(MineStates::kExploded);
  is_exploded_ = true;
}

bool Mine::IsExploded() const {
  return is_exploded_;
}

PixmapID Mine::GetPixmapId() const {
  return pixmap_component_->GetPixmapId();
}
