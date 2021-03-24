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
  const int car_start_pos_x_ = 360;
  const int car_start_pos_y_ = 548;
  const double car_start_angle_ = -M_PI / 2;
  Car car_;
  void ParseMapBorders();
  static std::pair<int, int> ParseLine(const QString& line);
};
