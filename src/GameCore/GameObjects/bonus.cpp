#include "bonus.h"

Bonus::Bonus(Vec2f point, BonusStates state) :
    GameObject(point),
    state_(state) {
  bonus_pixmap_component_.SetBonusPixmapId(state_);
}

void Bonus::BonusPixmapComponent::SetBonusPixmapId(BonusStates bonus_state) {
  auto category_value = static_cast<int32_t>(PixmapCategories::kBonus);
  auto bonus_state_value = static_cast<int32_t>(bonus_state);
  pixmap_id_ = (category_value << 24) + (bonus_state_value << 16);
}

void Bonus::ApplyTo(Car* car) {
  switch (state_) {
    case BonusStates::kHealth: {
      car->AddHitPoints(kBonusHealthPrize);
      break;
    }
    case BonusStates::kBulletsAmmo: {
      car->AddBulletsAmount(kBonusBulletsAmmoPrize);
      break;
    }
    case BonusStates::kMineAmmo: {
      car->AddMinesAmount(kBonusMinesPrize);
      break;
    }
  }
}

PixmapID Bonus::GetPixmapId() const {
  return bonus_pixmap_component_.GetPixmapId();
}
