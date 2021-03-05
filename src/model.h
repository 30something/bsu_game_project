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

 private:
  Car first_car{0, 0, 1000, 10};
};

