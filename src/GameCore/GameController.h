#pragma once

#include <utility>
#include <vector>

#include <QKeyEvent>
#include <QTextStream>
#include <QFile>
#include <QPoint>

#include "car.h"
#include "map.h"

class GameController {
 public:
  GameController();
  ~GameController() = default;

  void Tick(int time_millisec);

  void HandleKeyPressEvent(QKeyEvent* event);
  void HandleKeyReleaseEvent(QKeyEvent* event);

  std::pair<int, int> GetCarCoordinates() const;
  double GetCarAngle() const;

 private:
  const QPoint car_start_pos_ = {360, 548};
  const double car_start_angle_ = -M_PI / 2;
  Map* map_;
  Car car_;
};
