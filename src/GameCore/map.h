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
  explicit Map(uint map_index);
  void ParseMapBorders();
  static std::pair<int, int> ParseLine(const QString& line);
  void ProceedCollisions(Car* car);

 private:
  QString map_data_filename_;
  std::vector<std::vector<std::pair<int, int>>> borders_;
};
