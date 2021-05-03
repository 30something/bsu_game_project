#pragma once

#include <vector>

#include "src/GameCore/GameObjects/car.h"
#include "src/GameCore/GameObjects/game_object.h"

class Bonus : public GameObject {
 public:
  Bonus(Vec2f point, BonusTypes type);
  void ApplyTo(Car* car);
  PixmapID GetPixmapId() const override;

  bool operator==(const Bonus& rhs) const {
    return type_ == rhs.type_ &&
        position_ == rhs.position_;
  }

  bool operator!=(const Bonus& rhs) const {
    return !(rhs == *this);
  }

 private:
  class BonusPixmapComponent : public PixmapComponent {
   public:
    void SetBonusPixmapId(BonusTypes bonus_type);
  };

  BonusTypes type_;
  BonusPixmapComponent* pixmap_component_;

  static constexpr double kBonusHealthPrize = 20;
  static constexpr double kBonusBulletsAmmoPrize = 100;
  static constexpr double kBonusMinesPrize = 2;
};
