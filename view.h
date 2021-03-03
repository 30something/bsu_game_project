#pragma once

#include <vector>
#include <QApplication>
#include <QKeyEvent>
#include <QWidget>
#include <QPainter>
#include <QTime>


#include "helpers/vec_geometry.h"

class View : public QWidget {
 public:
  explicit View(QWidget* parent = nullptr);

  void paintEvent(QPaintEvent*) override;
  void timerEvent(QTimerEvent*) override;
  void keyPressEvent(QKeyEvent*) override;
  void keyReleaseEvent(QKeyEvent*) override;

 private:
  const int max_speed_forward_ = 6;
  const int max_speed_backward_ = -2;
  bool flag_left_ = false;
  bool flag_right_ = false;
  bool flag_up_ = false;
  bool flag_down_ = false;
  int timerId_;
  QImage car_;
  QImage map_;
  Vec2f velocity_;
  double x_ = 0;
  double y_ = 0;
};
