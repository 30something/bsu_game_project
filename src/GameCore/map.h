#pragma once

#include <utility>
#include <vector>

#include <QTextStream>
#include <QFile>

#include "src/helpers/vec2f.h"
#include "src/helpers/line.h"
#include "car.h"

class Map {
 public:
  void ParseMapBorders();
  static std::pair<int, int> ParseLine(const QString& line);
  void ProceedCollisions(Car* car);

 private:
  std::vector<std::vector<std::pair<int, int>>> borders_;
};
