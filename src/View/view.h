#pragma once

#include <utility>
#include <vector>

#include <QPainter>
#include <QImage>

#include "src/GameCore/GameController.h"
#include "EngineSound.h"
#include "DriftSound.h"
#include "src/helpers/sizes.h"

class View {
 public:
  View(QWidget* events_controller, GameController* model, GameMode* game_mode);
  ~View() = default;

  void Repaint(QPainter* painter);

  void ChangeEngineVolume(double coefficient);
  void PlayDrift(double coefficient);

 private:
  GameController* model_ = nullptr;
  QImage map_;
  QImage car_;
  int players_amount_ = 0;
  const double kScale = 2;
  void DrawMap(QPainter* painter,
               const QRect& frame,
               const QPoint& pos);
  void DrawCar(QPainter* painter,
               const QRect& frame,
               const QPoint& center,
               const QPoint& frame_center,
               double angle);
  std::vector<QRect> GetFramesVector(const QPainter* painter) const;
  Engine* engine_;
  Drift* drift_;
};
