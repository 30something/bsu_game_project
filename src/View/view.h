#pragma once

#include <utility>
#include <vector>

#include <QImage>
#include <QLabel>
#include <QPainter>
#include <QWidget>

#include "src/GameCore/GameController.h"
#include "src/helpers/sizes.h"

class View {
 public:
  View(QWidget* parent, GameController* model, GameMode* game_mode);
  ~View() = default;

  void Repaint(QPainter* painter);

  void UpdateStartLabel(const std::string& new_text);
  static void UpdateLapsLabel(QLabel* label, int laps_counter);
  static void UpdateVelocityLabel(QLabel* label, double velocity);

 private:
  void DrawMap(QPainter* painter,
               const QRect& frame,
               const QPoint& pos);
  void DrawCar(QPainter* painter,
               const QRect& frame,
               const QPoint& center,
               const QPoint& frame_center,
               double angle);

  std::vector<QRect> GetFramesVector(const QPainter* painter) const;

  GameController* model_ = nullptr;
  QWidget* parent_ = nullptr;
  QLabel* start_label_ = nullptr;
  std::vector<QLabel*> laps_labels_;
  std::vector<QLabel*> velocity_labels_;
  QImage map_;
  QImage car_;
  int players_amount_ = 0;
  const double kScale = 2;
};
