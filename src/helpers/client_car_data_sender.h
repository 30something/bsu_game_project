#pragma once

#include <QObject>
#include <QTimerEvent>

#include "src/Network/network_controller.h"
#include "src/GameCore/GameObjects/car.h"
#include "src/GameCore/Behaviors/behavior.h"

class ClientCarDataSender : public QObject {
 Q_OBJECT
 public:
  ClientCarDataSender(Car* car,
                      NetworkController* network_controller,
                      Behavior* behavior);
  void timerEvent(QTimerEvent* e) override;

 private:
  Car* car_;
  NetworkController* network_controller_;
  Behavior* behavior_;

  void SendCarData();
};



