#pragma once

#include <utility>
#include <vector>

#include <QPainter>
#include <QImage>

#include "src/GameCore/GameController.h"
#include "src/helpers/sizes.h"

class View {
 public:
  explicit View(GameController* model, int map_index);
  ~View() = default;

  void Repaint(QPainter* painter);

 private:
  GameController* model_ = nullptr;
  QImage map_;
  QImage car_;
  const double kScale = 2;
  void PaintCar(QPainter* painter,
                double width,
                double height,
                double angle) const;
};
