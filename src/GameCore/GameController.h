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
  explicit GameController(GameMode* game_mode);
  ~GameController() = default;

  void Tick(int time_millis);

  void HandleKeyPressEvent(QKeyEvent* event);
  void HandleKeyReleaseEvent(QKeyEvent* event);

  std::vector<QPoint> GetCarCoordinates() const;
  std::vector<double> GetCarAngles() const;

 private:
  const QPoint car1_start_pos_ = {360, 548};
  const double car1_start_angle_ = -M_PI / 2;
  const QPoint car2_start_pos_ = {380, 590};
  const double car2_start_angle_ = -M_PI / 2;
  static constexpr double kVelocityDecrease = 0.5;

  Map map_;
  std::vector<Car> cars_;
  GameMode* game_mode_ = nullptr;
  void ProceedCollisionsWithCars();
  static void CollideCars(Car* car_1, Car* car_2);
};
