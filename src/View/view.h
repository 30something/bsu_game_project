#pragma once

#include <string>
#include <utility>
#include <vector>
#include <map>

#include <QImage>
#include <QLabel>
#include <QPainter>
#include <QPixmap>
#include <QWidget>

#include "src/GameCore/game_controller.h"
#include "src/helpers/sizes.h"
#include "src/helpers/pixmap_loader.h"

class View {
 public:
  explicit View(GameMode* game_mode);
  ~View() = default;

  void Repaint(const std::vector<WrapperBase<GameObject>*>& objects,
               const std::vector<Vec2f>& players_cars_positions,
               QPainter* painter);
  void UpdateStartLabel(int seconds_before_start);
  void ClearStartLabel();

 private:
  void DrawMap(QPainter* painter,
               const QRect& frame,
               const Vec2f& pos);
  void DrawObjects(QPainter* painter,
                   const QRect& frame,
                   const Vec2f& frame_center,
                   const std::vector<WrapperBase<GameObject>*>& objects);
  void UpdateAllInfoDescription(QPainter* painter);
  std::vector<QRect> GetFramesVector(const QPainter* painter) const;

  QLabel* start_label_ = nullptr;
  PixmapLoader pixmap_loader_;

  uint32_t players_amount_ = 0;
  uint32_t laps_amount_ = 0;

  static constexpr double kScale = 2;
};
