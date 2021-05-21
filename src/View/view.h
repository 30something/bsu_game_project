#pragma once

#include <utility>
#include <vector>
#include <map>

#include <QPainter>
#include <QPixmap>

#include "src/GameCore/game_controller.h"
#include "src/helpers/sizes.h"
#include "src/helpers/pixmap_loader.h"

#include "engine_sound.h"
#include "drift_sound.h"
#include "brake_sound.h"
#include "sounds_of_effects.h"


class View {
 public:
  explicit View(QWidget* events_controller, GameController* model, GameMode* game_mode);
  ~View() = default;

  void Repaint(const std::vector<WrapperBase<GameObject>*>& objects,
               const std::vector<Vec2f>& players_cars_positions,
               QPainter* painter);
  void resizeEvent(int width, int height);
  std::vector<QRect> GetFrames() const;
  double GetScale() const;

  void PlayEngine(double speed_parameter, Motion motion_parameter, bool pause);
  void PlayDrift(double speed_parameter, bool car_is_alive, bool pause);
  void PlayBrake(double coefficient, bool pause);
  void PlayBonus(bool play_bonus);
  void PlayShooting(bool using_gun, bool bullets, bool enable_weapons, bool pause);
  void PlayMine(bool play_mine);
  void PlayCarExplosion(bool play_car_explosion);

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
  double scale_ = 0;

  Engine* engine_sound_;
  Drift* drift_sound_;
  Brake* brake_sound_;
  Effects* sounds_of_effects_;
  GameController* model_;
};
