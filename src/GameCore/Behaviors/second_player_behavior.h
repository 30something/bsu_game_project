#pragma once

#include "behavior.h"
#include "src/GameCore/input_controller.h"

class SecondPlayerBehavior : public Behavior {
 public:
  explicit SecondPlayerBehavior(const InputController* input_controller);
  void HandleTick(const GameObject*) override;

 private:
  const InputController* input_controller_ = nullptr;
};
