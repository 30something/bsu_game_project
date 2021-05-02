#pragma once

#include <vector>

#include "src/GameCore/GameObjects/car.h"
#include "src/GameCore/GameObjects/game_object.h"

class Bonus : public GameObject {
 public:
  Bonus(Vec2f point, BonusStates state);
  void ApplyTo(Car* car);
  PixmapID GetPixmapId() const override;

  bool operator==(const Bonus& rhs) const {
    return state_ == rhs.state_ &&
        position_ == rhs.position_;
  }

  bool operator!=(const Bonus& rhs) const {
    return !(rhs == *this);
  }

 private:
  class BonusPixmapComponent : public PixmapComponent {
   public:
    void SetBonusPixmapId(BonusStates bonus_state);
  };

  BonusStates state_;
  BonusPixmapComponent bonus_pixmap_component_;

  static constexpr double kBonusHealthPrize = 20;
  static constexpr double kBonusBulletsAmmoPrize = 100;
  static constexpr double kBonusMinesPrize = 2;
};
