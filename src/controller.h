#pragma once

#include <iostream>

#include <QWidget>
#include <QTimerEvent>
#include <QKeyEvent>
#include <QPainter>

#include "view.h"
#include "model.h"

class Controller : public QWidget {
 Q_OBJECT

 public:
  explicit Controller(QWidget* parent = nullptr);
  ~Controller() override = default;

  void timerEvent(QTimerEvent* event) override;
  void paintEvent(QPaintEvent* event) override;
  void KeyPressEvent(QKeyEvent* event);
  void KeyReleaseEvent(QKeyEvent* event);


 private:
  const int kMillisPerFrame = 20;

  Model* model_;
  View* view_;
};
