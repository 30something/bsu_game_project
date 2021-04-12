#pragma once

#include "behavior.h"
#include "src/GameCore/game_object.h"
#include "src/GameCore/car.h"

class SecondPlayerBehavior : public Behavior {
 public:
  void HandleTick() override;
  void HandleKeyPressEvent(GameObject*, QKeyEvent*) override;
  void HandleKeyReleaseEvent(GameObject* object, QKeyEvent*) override;
};
