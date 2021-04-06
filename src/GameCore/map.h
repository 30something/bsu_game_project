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
#include "src/helpers/json_parser.h"

class Map {
 public:
  explicit Map(JsonParser* parser);
  void ProceedCollisions(Car* car);

 private:
  JsonParser* parser_;
  std::vector<std::vector<QPoint>> borders_;

  static constexpr double kVelocityDecrease = 0.75;
  static constexpr double kHPDecrease = 0.005;

  static void CollideCar(Car* car, const Vec2f& point);
};
