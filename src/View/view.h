#pragma once

#include <utility>
#include <vector>
#include <map>

#include <QPainter>
#include <QPixmap>

#include "src/GameCore/game_controller.h"
#include "src/helpers/sizes.h"
#include "src/helpers/pixmap_loader.h"
#include "src/View/Sounds/engine_sound.h"
#include "src/View/Sounds/drift_sound.h"
#include "src/View/Sounds/brake_sound.h"
#include "src/View/Sounds/sounds_of_effects.h"
#include "src/View/Sounds/shooting_sound.h"

class View {
 public:
  explicit View(GameMode* game_mode);
  ~View() = default;

  void Repaint(const std::vector<WrapperBase<GameObject>*>& objects,
               const std::vector<Vec2f>& players_cars_positions,
               QPainter* painter);
  void resizeEvent(int width, int height);
  std::vector<QRect> GetFrames() const;
  double GetScale() const;

 private:
  void CalculateScale(int window_width, int window_height);
  void DrawMap(QPainter* painter,
               const QRect& frame,
               const Vec2f& pos);
  void DrawObjects(QPainter* painter,
                   const QRect& frame,
                   const Vec2f& frame_center,
                   const std::vector<WrapperBase<GameObject>*>& objects);
  void UpdateFrames(int width, int height);

  PixmapLoader pixmap_loader_;
  std::vector<QRect> frames_;

  uint32_t players_amount_ = 0;
  GameMode* game_mode_;
  double scale_ = 0;
};
