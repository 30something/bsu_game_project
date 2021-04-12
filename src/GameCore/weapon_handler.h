#pragma once

#include <vector>
#include <optional>

#include "mine.h"
#include "car.h"

class WeaponHandler {
 public:
  WeaponHandler() = default;
  ~WeaponHandler() = default;
  void PutMine(Car* car);
  void ProceedWeapons(std::vector<Car>* cars);
  const std::vector<Mine>& GetMines() const;

 private:
  std::vector<Mine> mines_;

  static void ShootBullet(Car* car, std::vector<Car>* cars);

  static constexpr int kMineSplash = 100;
  static constexpr double kBulletDamage = 0.1;
  static constexpr double kMineDamage = 20;
};
