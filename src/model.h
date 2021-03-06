#pragma once

#include <QKeyEvent>

#include "car.h"

class Model {
 public:
  Model() = default;
  ~Model() = default;

  void Tick(int time_millisec);

  // (Not inherited)
  void KeyPressEvent(QKeyEvent* event);
  // (Not inherited)
  void KeyReleaseEvent(QKeyEvent* event);
  std::pair<int, int> GetCarCoordinates();
  double GetCarAngle();

 private:
  Car first_car_{0, 0, 1000, 10};
};
