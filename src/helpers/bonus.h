#pragma once

#include <QPoint>

struct Bonus {
  enum class BonusType {
    kHealth = 0,
    kBulletsAmmo = 1,
    kMineAmmo = 2
  };

  Bonus(QPoint point, BonusType _type) :
      type(_type),
      position(point) {
  };
  BonusType type;
  QPoint position;

  bool operator==(const Bonus& rhs) const {
    return type == rhs.type &&
        position == rhs.position;
  }

  bool operator!=(const Bonus& rhs) const {
    return !(rhs == *this);
  }
};
