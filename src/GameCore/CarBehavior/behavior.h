#pragma once

#include <QKeyEvent>

#include "src/GameCore/game_object.h"

class Behavior {
 public:
  virtual void HandleTick(GameObject*) = 0;
  virtual void HandleKeyPressEvent(GameObject*, QKeyEvent*) = 0;
  virtual void HandleKeyReleaseEvent(GameObject*, QKeyEvent*) = 0;
};



