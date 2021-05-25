#include "second_player_behavior.h"

SecondPlayerBehavior::SecondPlayerBehavior(
    const InputController* input_controller) :
    input_controller_(input_controller) {}

void SecondPlayerBehavior::HandleTick(GameObject*) {
  auto keys_condition = input_controller_->GetKeysCondition();
  flag_up_ = keys_condition.at(KeyID::kSecondUp);
  flag_down_ = keys_condition.at(KeyID::kSecondDown);
  flag_left_ = keys_condition.at(KeyID::kSecondLeft);
  flag_right_ = keys_condition.at(KeyID::kSecondRight);
  flag_shoot_ = keys_condition.at(KeyID::kSecondShoot);
  flag_mine_ = keys_condition.at(KeyID::kSecondMine);
}
