#pragma once

#include <utility>
#include <vector>
#include <map>
#include <string>

#include <QPainter>
#include <QPixmap>

#include "src/GameCore/GameController.h"
#include "src/helpers/sizes.h"

class View {
 public:
  View(GameController* model, GameMode* game_mode);
  ~View() = default;

  void Repaint(QPainter* painter);

 private:
  GameController* model_ = nullptr;
  std::map<std::string, QPixmap> pixmaps_;
  std::map<std::string, QPoint> offsets_;
  int players_amount_ = 0;

  static constexpr double kScale = 1;

  void DrawMap(QPainter* painter,
               const QRect& frame,
               const Vec2f& pos);
  void DrawGameObjects(QPainter* painter,
                       const QRect& frame,
                       const Vec2f& frame_center,
                       const std::vector<const GameObject*>& game_objects);
  std::vector<QRect> GetFramesVector(const QPainter* painter) const;
  void PreparePixmaps(const GameMode* game_mode);
};
