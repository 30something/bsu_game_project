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
#include "src/helpers/physics.h"

class Map : public QObject {
  Q_OBJECT

 public:
  explicit Map(GameMode* game_mode);
  void HandleCarTick(Car* car);
  const std::vector<Bonus>& GetActiveBonuses() const;
  const std::vector<std::vector<Vec2f>>& GetBorders() const;
  const std::vector<Vec2f>& GetWaypoints() const;
  const std::vector<Line>& GetNoGoLines() const;
  const std::vector<std::pair<Vec2f, double>>& GetPosAndAngles() const;
  const Line& GetFinishLine() const;
  const Vec2f& GetNextWaypoint(uint32_t index) const;
  uint32_t GetWaypointsNumber() const;
  uint32_t GetNearestWaypointIndex(const Vec2f& point) const;

 private:
  void ProceedActiveBonuses(Car* car);
  void ProceedNewBonuses();
  void ProceedCollisions(Car*);
  void ProceedNewBonusFromNetwork();

  static void HandleCarCrashIntoBorder(Car* car, const Vec2f& point);

  static constexpr double kVelocityDecrease = 0.9;
  static constexpr double kHPDecrease = 0.0006;
  static constexpr size_t kMaxBonusesAmount = 5;
  static constexpr int32_t kMaxBonusSpawnDeviation = 15;
  static constexpr int32_t kAmountOfBonusTypes = 3;
  static constexpr int32_t kMaxMilliSecondsForNewBonus = 10000;
  static constexpr int32_t kMinMilliSecondForNewBonus = 1000;

  std::vector<std::vector<Vec2f>> borders_;
  std::vector<Vec2f> waypoints_;
  std::vector<Line> no_go_lines_;
  std::vector<std::pair<Vec2f, double>> pos_and_angles_;
  std::vector<Bonus> bonuses_;
  Line finish_line_;
  QTimer bonus_timer_;
  GameMode* game_mode_;
};
