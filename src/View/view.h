#pragma once

#include <string>
#include <utility>
#include <vector>

#include <QImage>
#include <QLabel>
#include <QPainter>
#include <QPixmap>
#include <QWidget>

#include "src/GameCore/GameController.h"
#include "src/helpers/sizes.h"

class View {
 public:
  View(QWidget* parent, GameController* model, GameMode* game_mode);
  ~View() = default;

  void Repaint(QPainter* painter);
  void UpdateStartLabel(const std::string& new_text);
  void UpdateInfoDescription(QPainter* painter);

 private:
  void DrawMap(QPainter* painter,
               const QRect& frame,
               const Vec2f& pos);
  void DrawPicture(
      QPainter* painter,
      const QRect& frame,
      const Vec2f& frame_center,
      const Vec2f& coords,
      double angle,
      const QPixmap& car,
      const QPoint& offset) const;
  std::vector<QRect> GetFramesVector(const QPainter* painter) const;

  GameController* model_ = nullptr;
  QPixmap map_;
  QPixmap car_;
  QPixmap dead_car_;
  QPixmap mine_;
  QPixmap shot_;
  QPixmap health_bonus_;
  QPixmap bullets_ammo_bonus_;
  QPixmap mines_bonus_;
  QLabel* start_label_ = nullptr;

  uint32_t players_amount_ = 0;
  uint32_t laps_amount_ = 0;

  const double kScale = 2;
};
