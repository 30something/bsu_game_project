#pragma once

#include <utility>
#include <vector>

#include <QTextStream>
#include <QRandomGenerator>
#include <QFile>
#include <QTimer>

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
  void HandleCarTick(Car* car);
  const std::vector<Bonus>& GetActiveBonuses() const;
  void SetBorders(const std::vector<std::vector<QPoint>>& borders);

 private:
  std::vector<std::vector<QPoint>> borders_;
  std::vector<QPoint> bonuses_positions_;
  std::vector<Bonus> bonuses_;
  QTimer bonus_timer_;

  static constexpr double kVelocityDecrease = 0.75;
  static constexpr double kHPDecrease = 0.001;
  static constexpr size_t kMaxBonusesAmount = 5;
  static constexpr size_t kAmountOfBonusTypes = 3;
  static constexpr size_t kMaxMilliSecondsForNewBonus = 20000;
  static constexpr size_t kMinMilliSecondForNewBonus = 5000;

  void CalculateBonusesPositions();
  void ProceedCollisions(Car*);
  void ProceedActiveBonuses(Car* car);
  void ProceedNewBonuses();

  static size_t FindIndexOfMinimalDistance(QPoint, const std::vector<QPoint>&);
  static void HandleCarCrashIntoBorder(Car* car, const Vec2f& point);
};
