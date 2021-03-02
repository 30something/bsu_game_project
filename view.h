#pragma once

#include <QWidget>
#include <QKeyEvent>
#include <vector>
#include <QApplication>
#include "helpers/vec_geometry.h"

class View : public QWidget {

 public:
  explicit View(QWidget* parent = 0);

  void paintEvent(QPaintEvent*) override;
  void timerEvent(QTimerEvent*) override;
  void keyPressEvent(QKeyEvent*) override;
  void keyReleaseEvent(QKeyEvent*) override;

 private:
  const int max_speed_forward = 6;
  const int max_speed_backward = -2;
  bool flag_left = false;
  bool flag_right = false;
  bool flag_up = false;
  bool flag_down = false;
  int timerId;
  QImage car_;
  QImage map;
  Vec2f velocity_;
  double x_ = 0;
  double y_ = 0;
};