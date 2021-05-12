#include "network_player_behavior.h"

NetworkPlayerBehavior::NetworkPlayerBehavior(
    NetworkController* network_controller,
    size_t our_id) :
    network_controller_(network_controller),
    our_id_(our_id) {
}

void NetworkPlayerBehavior::HandleTick(GameObject* game_object) {
  Car* car = dynamic_cast<Car*>(game_object);
  if (network_controller_->DataUpdated(our_id_)) {
    PlayerCarData our_data = network_controller_->GetPlayersData(our_id_);
    car->SetPosition(our_data.position);
    car->SetAngleVec(our_data.angle);
    car->SetHitPoints(our_data.hp);
    flag_up_ = our_data.flag_up;
    flag_down_ = our_data.flag_down;
    flag_left_ = our_data.flag_left;
    flag_right_ = our_data.flag_right;
    flag_shoot_ = our_data.flag_shoot;
    flag_mine_ = our_data.flag_mine;
  }
}
