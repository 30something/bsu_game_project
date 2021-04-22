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

std::vector<Line> Bonus::GetCollisionLines() const {
  Vec2f p1(position_.GetX() - kBonusRadius, position_.GetY() - kBonusRadius);
  Vec2f p2(position_.GetX() + kBonusRadius, position_.GetY() - kBonusRadius);
  Vec2f p3(position_.GetX() + kBonusRadius, position_.GetY() + kBonusRadius);
  Vec2f p4(position_.GetX() - kBonusRadius, position_.GetY() + kBonusRadius);
  Line l1(p1, p2);
  Line l2(p2, p3);
  Line l3(p3, p4);
  Line l4(p4, p1);
 return {l1,l2,l3,l4};
}
