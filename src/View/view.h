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
#include "shooting_sound.h"

class View {
 public:
  explicit View(QWidget* events_controller, GameMode* game_mode);
  ~View() = default;

  void Repaint(const std::vector<WrapperBase<GameObject>*>& objects,
               const std::vector<Vec2f>& players_cars_positions,
               QPainter* painter);
  void resizeEvent(int width, int height);
  std::vector<QRect> GetFrames() const;
  double GetScale() const;

  void PlayEngine(const std::vector<EngineParameters>& engine_parameters,
                  bool pause);
  void PlayDrift(std::vector<DriftParameters> drift_parameters, bool pause);
  void PlayBrake(std::vector<BrakeParameters> brake_parameters, bool pause);
  void PlayBonus(bool play_bonus);
  void PlayShooting(std::vector<ShootingParameters> shooting_parameters,
                    bool pause);
  void PlayMine(EffectParameters explosion_parameters);
  void PlayCarExplosion(EffectParameters explosion_parameters);

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
  uint32_t cars_amount_ = 0;
  GameMode* game_mode_;
  double scale_ = 0;

  std::vector<Engine*> engine_sounds_;
  std::vector<Drift*> drift_sounds_;
  std::vector<Brake*> brake_sounds_;
  std::vector<Shooting*> shooting_sounds_;
  Effects sounds_of_effects_;
};
