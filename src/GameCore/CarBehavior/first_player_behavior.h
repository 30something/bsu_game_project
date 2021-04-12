#pragma once

#include "behaviour.h"

class FirstPlayerBehavior : public Behaviour {
  void HandleTick() override;
  void HandleKeyPressEvent(QKeyEvent*) override;
  void HandleKeyReleaseEvent(QKeyEvent*) override;
};
