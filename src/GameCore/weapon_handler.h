#pragma once

#include <vector>
#include <optional>

#include "src/GameCore/GameObjects/mine.h"
#include "src/GameCore/GameObjects/car.h"
#include "src/GameCore/GameObjects/animation.h"

class WeaponHandler {
 public:
  WeaponHandler() = default;
  ~WeaponHandler() = default;
  void PutMine(Car* car);
  void ProceedWeapons(std::vector<Car>* cars,
                      std::vector<Animation>* animations);
  const std::vector<Mine>& GetMines() const;
  void SetEnableWeapons(bool enable_weapons);

 private:
  std::vector<Mine> mines_;
  static void ShootBullet(Car* car, std::vector<Car>* cars);
  bool enable_weapons_ = false;
  static constexpr int kMineSplash = 100;
  static constexpr double kBulletDamage = 0.3;
  static constexpr double kMineDamage = 20;
};
