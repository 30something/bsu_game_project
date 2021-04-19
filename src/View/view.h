#pragma once

#include <utility>
#include <vector>

#include <QPainter>
#include <QPixmap>

#include "src/GameCore/GameController.h"
#include "EngineSound.h"
#include "DriftSound.h"
#include "BrakeSound.h"
#include "SoundsOfEffects.h"
#include "src/helpers/sizes.h"

class View {
 public:
  View(QWidget* events_controller, GameController* model, GameMode* game_mode);
  ~View() = default;

  void Repaint(QPainter* painter);

  void PlayEngine(double coefficient, int direction, bool car_is_alive);
  void PlayDrift(double coefficient);
  void PlayBrake(double coefficient);
  void PlayBonus(bool play_bonus);
  void PlayShooting(bool using_gun, bool bullets);
  void PlayMine(bool play_mine);
  void PlayCarExplosion(bool play_car_explosion);

 private:
  GameController* model_ = nullptr;
  QPixmap map_;
  QPixmap car_;
  QPixmap dead_car_;
  QPixmap mine_;
  QPixmap shot_;
  QPixmap health_bonus_;
  QPixmap bullets_ammo_bonus_;
  QPixmap mines_bonus_;

  int players_amount_ = 0;

  const double kScale = 2;

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
  Engine* engine_;
  Drift* drift_;
  Brake* brake_;
  Effects* effects_;
};
