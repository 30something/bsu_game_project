#pragma once

#include <utility>
#include <vector>

#include <QTextStream>
#include <QFile>

#include "src/helpers/vec2f.h"
#include "src/helpers/line.h"
#include "car.h"
#include "src/helpers/map_data.h"
#include "src/helpers/game_mode.h"

class Map {
 public:
  explicit Map(GameMode* game_mode);
  void ParseMapBorders();
  static std::pair<int, int> ParseLine(const QString& line);
  void ProceedCollisions(Car* car);

 private:
  uint map_index_ = 0;
  static constexpr double kVelocityDecrease = 0.75;
  std::vector<std::vector<std::pair<int, int>>> borders_;
  static void CollideCar(Car* car, const Vec2f& point);
};
