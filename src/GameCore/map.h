#pragma once

#include <utility>
#include <vector>
#include <QRandomGenerator>

#include <QTextStream>
#include <QFile>

#include "src/helpers/vec2f.h"
#include "src/helpers/line.h"
#include "car.h"
#include "src/helpers/map_data.h"
#include "src/helpers/game_mode.h"
#include "src/helpers/json_map_parser.h"
#include "src/helpers/bonus.h"

class Map {
 public:
  Map() = default;
  explicit Map(std::vector<std::vector<QPoint>> borders);
  void Tick(Car* car);
  const std::vector<Bonus>& GetActiveBonuses() const;

 private:
  std::vector<std::vector<QPoint>> borders_;
  std::vector<QPoint> bonuses_positions_;
  std::vector<Bonus> active_bonuses_;

  static constexpr double kVelocityDecrease = 0.75;
  static constexpr double kHPDecrease = 0.001;
  static constexpr double kBonusHealthPrize = 20;
  static constexpr double kBonusBulletsAmmoPrize = 100;
  static constexpr double kBonusMinesPrize = 2;
  static constexpr int kMaxBonusesAmount = 5;
  static constexpr int kBonusProbability = 100000;

  void CalculateBonusesPositions();
  void ProceedCollisions(Car*);
  void ProceedActiveBonuses(Car* car);
  void ProceedNewBonuses();

 private:
  static size_t FindIndexOfMinimalDistance(QPoint, const std::vector<QPoint>&);
  static void CollideCar(Car* car, const Vec2f& point);
};
