#pragma once

#include "behavior.h"

class SecondPlayerBehavior : public Behavior {
 public:
  void HandleTick() override;
};
