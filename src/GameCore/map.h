#pragma once

#include <QTextStream>
#include <QFile>
#include "src/helpers/vec2f.h"
#include "src/helpers/line.h"

class Map {
 public:
  void ParseMapBorders();
  static std::pair<int, int> ParseLine(const QString& line);
  bool ProceedCollisions(std::vector<Vec2f>& corners);

 private:
  std::vector<std::vector<std::pair<int, int>>> borders_;
};
