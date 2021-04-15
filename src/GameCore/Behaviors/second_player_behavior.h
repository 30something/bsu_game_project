#pragma once

#include "behavior.h"
#include "src/GameCore/input_controller.h"

class SecondPlayerBehavior : public Behavior {
 public:
  explicit SecondPlayerBehavior(InputController* input_controller);
  void HandleTick() override;

 private:
  InputController* input_controller_ = nullptr;
};
