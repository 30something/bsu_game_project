#pragma once

#include <utility>
#include <vector>

#include <QPainter>
#include <QImage>

#include "src/GameCore/GameController.h"
#include "src/helpers/sizes.h"

class View {
 public:
  explicit View(GameController* model, GameMode* game_mode);
  ~View() = default;

  void Repaint(QPainter* painter);

 private:
  GameController* model_ = nullptr;
  QImage map_;
  QImage car_;
  const double kScale = 2;
  int amount_of_players_ = 0;
  void DrawMap(QPainter* painter,
               const QRect& frame,
               const QPoint& pos);
  void DrawCar(QPainter* painter,
               const QRect& frame,
               const QPoint& center,
               const QPoint& frame_center,
               double angle);
};
