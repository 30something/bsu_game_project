#pragma once

#include <utility>
#include <vector>

#include <QPainter>
#include <QImage>

#include "src/GameCore/GameController.h"
#include "src/helpers/sizes.h"

class View {
 public:
  View(GameController* model, GameMode* game_mode);
  ~View() = default;

  void Repaint(QPainter* painter);

 private:
  GameController* model_ = nullptr;
  QImage map_;
  QImage car_;
  QImage mine_;
  QImage shot_;
  int players_amount_ = 0;
  const double kScale = 2;
  void DrawMap(QPainter* painter,
               const QRect& frame,
               const Vec2f& pos);
  void DrawCar(QPainter* painter,
               const QRect& frame,
               const Vec2f& center,
               const Vec2f& frame_center,
               double angle,
               const QImage& car);
  void DrawMine(QPainter* painter,
                const QRect& frame,
                const Vec2f& frame_center,
                const QPoint& mine);
  void DrawShot(QPainter* painter,
                const QRect& frame,
                const Vec2f& frame_center,
                const Vec2f& coord,
                double angle);
  std::vector<QRect> GetFramesVector(const QPainter* painter) const;
};
