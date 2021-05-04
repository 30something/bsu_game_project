#include "mine.h"

Mine::Mine(Vec2f position) :
  GameObject(position,
             new MinePixmapComponent) {
  dynamic_cast<MinePixmapComponent*>(pixmap_component_.get())->
      SetMinePixmapId(MineStates::kStandard);
}

bool Mine::operator==(const Mine& rhs) const {
  return position_ == rhs.position_;
}

bool Mine::operator!=(const Mine& rhs) const {
  return !(rhs == *this);
}

void Mine::SetExploded() {
  dynamic_cast<MinePixmapComponent*>(pixmap_component_.get())->
      SetMinePixmapId(MineStates::kExploded);
  is_exploded_ = true;
}

bool Mine::IsExploded() const {
  return is_exploded_;
}

void Mine::MinePixmapComponent::SetMinePixmapId(MineStates mine_state) {
  auto category_value = static_cast<int32_t>(PixmapCategories::kMine);
  auto mine_state_value = static_cast<int32_t>(mine_state);
  pixmap_id_ = (category_value << 24) + (mine_state_value << 16);
}
