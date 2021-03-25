#pragma once

#include <utility>
#include <vector>

#include <QTextStream>
#include <QFile>

#include "src/helpers/vec2f.h"
#include "src/helpers/line.h"

class Map {
 public:
  void ParseMapBorders();
  static std::pair<int, int> ParseLine(const QString& line);
  bool ProceedCollisions(const std::vector<Line>& lines);

 private:
  std::vector<std::vector<std::pair<int, int>>> borders_;
};
