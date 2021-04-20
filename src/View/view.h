#pragma once

#include <utility>
#include <vector>
#include <map>

#include <QPainter>
#include <QPixmap>

#include "src/GameCore/GameController.h"
#include "src/helpers/sizes.h"
#include "src/helpers/pixmap_loader.h"

class View {
 public:
  explicit View(GameMode* game_mode);
  ~View() = default;

  void Repaint(const std::vector<WrapperBase<GameObject>*>& objects,
               const std::vector<Vec2f>& players_cars_positions,
               QPainter* painter);
  void resizeEvent(int width, int height);

 private:
  int players_amount_ = 0;
  double scale_ = 0;
  PixmapLoader pixmap_loader_;

  void CalculateScale(int window_width, int window_height);
  void DrawMap(QPainter* painter,
               const QRect& frame,
               const Vec2f& pos);
  void DrawObjects(QPainter* painter,
                   const QRect& frame,
                   const Vec2f& frame_center,
                   const std::vector<WrapperBase<GameObject>*>& objects);
  std::vector<QRect> GetFramesVector(const QPainter* painter) const;
};
