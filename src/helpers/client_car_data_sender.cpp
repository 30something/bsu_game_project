#include "client_car_data_sender.h"

ClientCarDataSender::ClientCarDataSender(Car* car,
                                         NetworkController* network_controller,
                                         Behavior* behavior) :
    QObject(nullptr),
    car_(car),
    network_controller_(network_controller),
    behavior_(behavior) {
  startTimer(network::kMillisDataSend);
}

void ClientCarDataSender::timerEvent(QTimerEvent*) {
  SendCarData();
}

void ClientCarDataSender::SendCarData() {
  PlayerCarData data;
  data.angle = car_->GetAngleVec();
  data.position = car_->GetPosition();
  data.hp = car_->GetHitPoints();
  data.flag_up = behavior_->IsFlagUp();
  data.flag_down = behavior_->IsFlagDown();
  data.flag_left = behavior_->IsFlagLeft();
  data.flag_right = behavior_->IsFlagRight();
  data.flag_shoot = behavior_->IsFlagShoot();
  data.flag_mine = behavior_->IsFlagMine();
  network_controller_->SendCarData(data);
}
