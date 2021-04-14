#pragma once

#include <QKeyEvent>

#include "src/GameCore/car.h"

class InputController {
 public:
  InputController() = default;
  void HandleKeyPressEvent(QKeyEvent* event,
                           Car* first_car,
                           Car* second_car = nullptr);
  void HandleKeyReleaseEvent(QKeyEvent* event,
                             Car* first_car,
                             Car* second_car = nullptr);
};
