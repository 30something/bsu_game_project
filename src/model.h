#pragma once

#include <QKeyEvent>

#include "car.h"



class Model {
 public:
  Model() = default;
  ~Model() = default;

  void Tick(int time_millisec);
  void KeyPressEvent(QKeyEvent* event);
  void KeyReleaseEvent(QKeyEvent* event);

 private:
  Car first_car;
};

