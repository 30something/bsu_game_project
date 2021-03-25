#pragma once

#include <QPainter>
#include <QImage>

#include "src/GameCore/GameController.h"

class View {
 public:
  explicit View(Model* model);
  ~View() = default;

  void Repaint(QPainter* painter);

 private:
  Model* model_ = nullptr;
  QImage map_;
  QImage car_;
};
