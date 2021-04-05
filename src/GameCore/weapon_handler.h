#pragma once

#include <vector>

#include <QPoint>

#include "car.h"

class WeaponHandler {
 public:
  explicit WeaponHandler(std::vector<Car>* cars);
  ~WeaponHandler() = default;
  void PutMine(Car* car);
  void ProceedWeapons();
  const std::vector<QPoint>& GetMines() const;

 private:
  std::vector<Car>* cars_;
  std::vector<QPoint> mines_;

  void ShotBullet(Car* car);
  static bool CarIsAboveMine(const Car& car, const QPoint& mine);
  static int Product(const QPoint&, const QPoint& p1, const QPoint& p2);

  static constexpr int kPutMineOffset = -10;
  static constexpr double kBulletDamage = 0.1;
  static constexpr double kShootingRange = 100;
  static constexpr double kMineDamage = 20;
};
