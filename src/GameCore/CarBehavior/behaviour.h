#pragma once

#include <QKeyEvent>

class Behaviour {
  virtual void HandleTick() = 0;
  virtual void HandleKeyPressEvent(QKeyEvent*) = 0;
  virtual void HandleKeyReleaseEvent(QKeyEvent*) = 0;
};



