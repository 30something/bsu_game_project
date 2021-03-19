#pragma once

#include <utility>
#include <vector>

#include <QKeyEvent>
#include <QTextStream>
#include <QFile>

#include "src/Model/car.h"

class Model {
 public:
  Model();
  ~Model() = default;

  void Tick(int time_millisec);

  void HandleKeyPressEvent(QKeyEvent* event);
  void HandleKeyReleaseEvent(QKeyEvent* event);

  std::pair<int, int> GetCarCoordinates() const;
  double GetCarAngle() const;

 private:
  std::vector<std::vector<std::pair<int, int>>>* borders_ = nullptr;
  Car car_;

  void ParseMapBorders();
  static std::pair<int, int> ParseLine(const QString& line);
};
