#pragma once

#include <utility>
#include <vector>
#include <map>

#include "src/GameCore/game_controller.h"
#include "src/helpers/sizes.h"
#include "src/helpers/pixmap_loader.h"
#include "src/View/Sounds/engine_sound.h"
#include "src/View/Sounds/drift_sound.h"
#include "src/View/Sounds/brake_sound.h"
#include "src/View/Sounds/sounds_of_effects.h"
#include "src/View/Sounds/shooting_sound.h"

class Sound {
 public:
  Sound(QWidget* events_controller, GameMode* game_mode);

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
  std::vector<Engine*> engine_sounds_;
  std::vector<Drift*> drift_sounds_;
  std::vector<Brake*> brake_sounds_;
  std::vector<Shooting*> shooting_sounds_;
  Effects sounds_of_effects_;
  GameMode* game_mode_;
  uint32_t cars_amount_ = 0;
};



