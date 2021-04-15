#include "first_player_behavior.h"

FirstPlayerBehavior::FirstPlayerBehavior(InputController* input_controller) :
input_controller_(input_controller) {}

void FirstPlayerBehavior::HandleTick() {
  auto keys_condition = input_controller_->GetKeysCondition();
  flag_up_ = keys_condition.at(KeyID::kFirstUp);
  flag_down_ = keys_condition.at(KeyID::kFirstDown);
  flag_left_ = keys_condition.at(KeyID::kFirstLeft);
  flag_right_ = keys_condition.at(KeyID::kFirstRight);
  flag_shoot_ = keys_condition.at(KeyID::kFirstShoot);
  flag_mine_ = keys_condition.at(KeyID::kFirstMine);
}
