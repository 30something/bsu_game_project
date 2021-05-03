#include "bonus.h"

Bonus::Bonus(Vec2f point, BonusTypes type) :
    GameObject(point),
    type_(type),
    pixmap_component_(new BonusPixmapComponent) {
  pixmap_component_->SetBonusPixmapId(type_);
}

void Bonus::BonusPixmapComponent::SetBonusPixmapId(BonusTypes bonus_type) {
  auto category_value = static_cast<int32_t>(PixmapCategories::kBonus);
  auto bonus_state_value = static_cast<int32_t>(bonus_type);
  pixmap_id_ = (category_value << 24) + (bonus_state_value << 16);
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

PixmapID Bonus::GetPixmapId() const {
  return pixmap_component_->GetPixmapId();
}
