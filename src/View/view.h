#pragma once

#include <utility>
#include <vector>

#include <QPainter>
#include <QImage>

#include "src/GameCore/GameController.h"

class View {
 public:
  explicit View(GameController* model, int map_index);
  ~View() = default;

  void Repaint(QPainter* painter);

 private:
  GameController* model_ = nullptr;
  QImage map_;
  QImage car_;
};
