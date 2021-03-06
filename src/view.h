#pragma once

#include <QPainter>
#include <QImage>

#include "model.h"


class View {
 public:
  explicit View(Model* model);
  ~View() = default;

  void Repaint(QPainter* painter);

 private:
  Model* model_;
  QImage map_;
  QImage car_;
};
