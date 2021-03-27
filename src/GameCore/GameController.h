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
  explicit GameController(uint map_index);
  ~GameController() = default;

  void Tick(int time_millis);

  void HandleKeyPressEvent(QKeyEvent* event);
  void HandleKeyReleaseEvent(QKeyEvent* event);

  std::vector<std::pair<int, int>> GetCarCoordinates() const;
  std::vector<double> GetCarAngles() const;

 private:
  const QPoint car1_start_pos_ = {360, 548};
  const double car1_start_angle_ = -M_PI / 2;
  const QPoint car2_start_pos_ = {380, 590};
  const double car2_start_angle_ = -M_PI / 2;
  Map map_;
  std::vector<Car> cars_;
  void ProceedColisionsWithCars();
};
