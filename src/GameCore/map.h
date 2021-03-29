#pragma once

#include <utility>
#include <vector>

#include <QTextStream>
#include <QFile>

#include "src/helpers/vec2f.h"
#include "src/helpers/line.h"
#include "car.h"
#include "src/helpers/map_data.h"

class Map {
 public:
  explicit Map(uint map_index);
  void ParseMapBorders();
  static std::pair<int, int> ParseLine(const QString& line);
  void ProceedCollisions(Car* car);

 private:
  uint map_index_ = 0;
  std::vector<std::vector<std::pair<int, int>>> borders_;
  static void CollideCar(Car* car, const Vec2f& point) ;
};
