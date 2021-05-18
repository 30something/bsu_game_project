#pragma once

#include "behavior.h"
#include "src/GameCore/GameObjects/car.h"
#include "src/Network/network_controller.h"
#include "src/Network/network_helpers.h"

class NetworkPlayerBehavior : public Behavior {
 public:
  explicit NetworkPlayerBehavior(NetworkController* network_controller,
                                 size_t our_id);
  void HandleTick(GameObject*) override;

 private:
  NetworkController* network_controller_ = nullptr;
  size_t our_id_;
};
