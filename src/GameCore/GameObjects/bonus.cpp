#include "bonus.h"

Bonus::Bonus(Vec2f point, BonusType _type) :
    GameObject(point),
    type_(_type) {
  switch (type_) {
    case BonusType::kMineAmmo: {
      pixmap_id_ = PixmapID::kBonusMineAmmo;
      break;
    }
    case BonusType::kBulletsAmmo: {
      pixmap_id_ = PixmapID::kBonusBulletsAmmo;
      break;
    }
    default: {
      pixmap_id_ = PixmapID::kBonusHealth;
    }
  }
}

void Bonus::ApplyTo(Car* car) {
  switch (type_) {
    case BonusType::kHealth: {
      car->AddHitPoints(kBonusHealthPrize);
      break;
    }
    case BonusType::kBulletsAmmo: {
      car->AddBulletsAmount(kBonusBulletsAmmoPrize);
      break;
    }
    case BonusType::kMineAmmo: {
      car->AddMinesAmount(kBonusMinesPrize);
      break;
    }
  }
}
