#pragma once

#include <vector>
#include <optional>

#include <QPoint>

#include "car.h"

class WeaponHandler {
 public:
  WeaponHandler() = default;
  ~WeaponHandler() = default;
  void PutMine(Car* car);
  void ProceedWeapons(std::vector<Car>* cars);
  const std::vector<QPoint>& GetMinesCoordinates() const;

  bool MineIsExploded() const;

 private:
  std::vector<QPoint> mines_;

  static void ShootBullet(Car* car, std::vector<Car>* cars);

  static constexpr int kMineSplash = 100;
  static constexpr double kBulletDamage = 0.1;
  static constexpr double kMineDamage = 20;

  bool mine_is_exploded_ = false;
};
