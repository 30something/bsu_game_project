#pragma once

#include <utility>

#include <QKeyEvent>

#include "car.h"

class Model {
 public:
  Model() = default;
  ~Model() = default;

  void Tick(int time_millisec);

  void HandleKeyPressEvent(QKeyEvent* event);
  void HandleKeyReleaseEvent(QKeyEvent* event);

  std::pair<int, int> GetCarCoordinates() const;
  double GetCarAngle() const;

 private:
  Car car_{0.0, 0.0};
};
