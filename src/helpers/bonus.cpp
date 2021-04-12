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

const Vec2f& Bonus::GetPosition() const {
  return position_;
}

double Bonus::GetAngle() const {
  return 0;
}

std::string Bonus::GetPixmapId() const {
  switch (type_) {
    case BonusType::kMineAmmo: {
      return "bonus_mine_ammo";
    }
    case BonusType::kBulletsAmmo: {
      return "bonus_bullets_ammo";
    }
    case BonusType::kHealth: {
      return "bonus_health";
    }
  }
}

std::vector<Line> Bonus::GetLines() const {
  return std::vector<Line>();
}
