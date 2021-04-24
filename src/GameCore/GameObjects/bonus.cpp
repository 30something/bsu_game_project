#include "bonus.h"

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

PixmapID Bonus::GetPixmapId() const {
  switch (type_) {
    case BonusType::kMineAmmo: {
      return PixmapID::kBonusMineAmmo;
    }
    case BonusType::kBulletsAmmo: {
      return PixmapID::kBonusBulletsAmmo;
    }
    default: {
      return PixmapID::kBonusHealth;
    }
  }
}
