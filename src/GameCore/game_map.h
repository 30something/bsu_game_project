#pragma once

#include <utility>
#include <vector>

#include <QTextStream>
#include <QRandomGenerator>
#include <QFile>
#include <QTimer>

#include "src/helpers/vec2f.h"
#include "src/helpers/line.h"
#include "src/GameCore/GameObjects/car.h"
#include "src/helpers/map_data.h"
#include "src/helpers/game_mode.h"
#include "src/helpers/json_map_parser.h"
#include "src/GameCore/GameObjects/bonus.h"

class Map {
 public:
  Map() = default;
  void HandleCarTick(Car* car);
  const std::vector<Bonus>& GetActiveBonuses() const;
  void SetBorders(const std::vector<std::vector<QPoint>>& borders);
  void ProceedCollisions(Car* car);

 private:
  void CalculateBonusesPositions();
  void ProceedCollisions(Car*);
  void ProceedActiveBonuses(Car* car);
  void ProceedNewBonuses();

  static size_t FindIndexOfMinimalDistance(QPoint, const std::vector<QPoint>&);
  static void HandleCarCrashIntoBorder(Car* car, const Vec2f& point);

  static constexpr double kVelocityDecrease = 0.75;
  static constexpr double kHPDecrease = 0.001;
  static constexpr size_t kMaxBonusesAmount = 5;
  static constexpr int kAmountOfBonusTypes = 3;
  static constexpr int kMaxMilliSecondsForNewBonus = 10000;
  static constexpr int kMinMilliSecondForNewBonus = 1000;

  std::vector<std::vector<QPoint>> borders_;
  std::vector<Vec2f> bonuses_positions_;
  std::vector<Bonus> bonuses_;
  QTimer bonus_timer_;
};
