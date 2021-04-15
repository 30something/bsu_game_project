#pragma once

#include "behavior.h"
#include "src/GameCore/input_controller.h"

class FirstPlayerBehavior : public Behavior {
 public:
  explicit FirstPlayerBehavior(InputController* input_controller);
  void HandleTick() override;

 private:
  InputController* input_controller_ = nullptr;
};
