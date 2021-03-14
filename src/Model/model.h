#pragma once

#include <utility>

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
  std::vector<std::pair<int, int>>* left_borders_;
  std::vector<std::pair<int, int>>* right_borders_;
  Car car_;

  void ParseMapBorders();
  static std::pair<int, int> ParseLine(const QString& line);
};
