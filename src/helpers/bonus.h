#pragma once

#include <QPoint>

#include "src/GameCore/car.h"

class Bonus {
 public:
  enum class BonusType {
    kHealth = 0,
    kBulletsAmmo = 1,
    kMineAmmo = 2
  };

  Bonus(QPoint point, BonusType _type) :
      type_(_type),
      position_(point) {
  }

  void ApplyTo(Car* car);
  BonusType GetType() const;
  const QPoint& GetPosition() const;

  bool operator==(const Bonus& rhs) const {
    return type_ == rhs.type_ &&
        position_ == rhs.position_;
  }

  bool operator!=(const Bonus& rhs) const {
    return !(rhs == *this);
  }

 private:
  BonusType type_;
  QPoint position_;

  static constexpr double kBonusHealthPrize = 20;
  static constexpr double kBonusBulletsAmmoPrize = 100;
  static constexpr double kBonusMinesPrize = 2;
};
