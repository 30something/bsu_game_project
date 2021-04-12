#pragma once

#include <string>
#include <vector>

#include "src/GameCore/car.h"
#include "src/GameCore/game_object.h"

class Bonus : public GameObject {
 public:
  enum class BonusType {
    kHealth = 0,
    kBulletsAmmo = 1,
    kMineAmmo = 2
  };

  Bonus(Vec2f point, BonusType _type) :
      type_(_type),
      position_(point) {
  }

  void ApplyTo(Car* car);
  const Vec2f& GetPosition() const override;
  double GetAngle() const override;
  std::string GetPixmapId() const override;
  std::vector<Line> GetLines() const override;

  bool operator==(const Bonus& rhs) const {
    return type_ == rhs.type_ &&
        position_ == rhs.position_;
  }

  bool operator!=(const Bonus& rhs) const {
    return !(rhs == *this);
  }

 private:
  BonusType type_;
  Vec2f position_;

  static constexpr double kBonusHealthPrize = 20;
  static constexpr double kBonusBulletsAmmoPrize = 100;
  static constexpr double kBonusMinesPrize = 2;
};
