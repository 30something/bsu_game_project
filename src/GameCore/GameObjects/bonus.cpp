#include "bonus.h"

Bonus::Bonus(Vec2f point, BonusTypes type) :
    GameObject(point,
               new BonusPixmapComponent),
    type_(type) {
  dynamic_cast<BonusPixmapComponent*>(pixmap_component_.get())->
      SetBonusPixmapId(type_);
}

void Bonus::ApplyTo(Car* car) {
  switch (type_) {
    case BonusTypes::kHealth: {
      car->AddHitPoints(kBonusHealthPrize);
      break;
    }
    case BonusTypes::kBulletsAmmo: {
      car->AddBulletsAmount(kBonusBulletsAmmoPrize);
      break;
    }
    case BonusTypes::kMineAmmo: {
      car->AddMinesAmount(kBonusMinesPrize);
      break;
    }
  }
}

void Bonus::BonusPixmapComponent::SetBonusPixmapId(BonusTypes bonus_type) {
  auto category_value = static_cast<int32_t>(PixmapCategories::kBonus);
  auto bonus_state_value = static_cast<int32_t>(bonus_type);
  pixmap_id_ = (category_value << 24) + (bonus_state_value << 16);
}
