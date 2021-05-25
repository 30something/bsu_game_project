#include "sound.h"

Sound::Sound(QWidget* events_controller, GameMode* game_mode) :
    sounds_of_effects_(new Effects(events_controller)),
    game_mode_(game_mode),
    cars_amount_(
        game_mode->players_amount + game_mode->network_players_amount +
            game_mode->bots_amount) {
  engine_sounds_.reserve(cars_amount_);
  drift_sounds_.reserve(cars_amount_);
  brake_sounds_.reserve(cars_amount_);
  shooting_sounds_.reserve(cars_amount_);

  for (uint32_t i = 0; i < cars_amount_; i++) {
    engine_sounds_.push_back(new Engine(
        events_controller, game_mode_->volume_settings_parameter));
    drift_sounds_.push_back(new Drift(events_controller));
    brake_sounds_.push_back(new Brake(events_controller));
    shooting_sounds_.push_back(new Shooting(events_controller));
  }
}

void Sound::PlayEngine(const std::vector<EngineParameters>& engine_parameters,
                       bool pause) {
  for (uint32_t i = 0; i < cars_amount_; i++) {
    engine_sounds_.at(i)->Play(engine_parameters.at(i).speed_parameter,
                               engine_parameters.at(i).motion_parameter,
                               engine_parameters.at(i).volume_parameter,
                               game_mode_->volume_settings_parameter,
                               pause);
  }
}

void
Sound::PlayDrift(std::vector<DriftParameters> drift_parameters, bool pause) {
  for (uint32_t i = 0; i < cars_amount_; i++) {
    drift_sounds_.at(i)->Play(drift_parameters.at(i).speed_parameter,
                              drift_parameters.at(i).enable_drifting,
                              drift_parameters.at(i).volume_parameter,
                              game_mode_->volume_settings_parameter,
                              pause);
  }
}

void
Sound::PlayBrake(std::vector<BrakeParameters> brake_parameters, bool pause) {
  for (uint32_t i = 0; i < cars_amount_; i++) {
    brake_sounds_.at(i)->Play(brake_parameters.at(i).speed_parameter,
                              brake_parameters.at(i).volume_parameter,
                              game_mode_->volume_settings_parameter,
                              pause);
  }
}

void Sound::PlayBonus(bool play_bonus) {
  sounds_of_effects_.PlayBonus(play_bonus,
                               game_mode_->volume_settings_parameter);
}

void Sound::PlayShooting(std::vector<ShootingParameters> shooting_parameters,
                         bool pause) {
  for (uint32_t i = 0; i < cars_amount_; i++) {
    shooting_sounds_.at(i)->Play(shooting_parameters.at(i).using_gun,
                                 shooting_parameters.at(i).bullets,
                                 shooting_parameters.at(i).enable_weapons,
                                 shooting_parameters.at(i).volume_parameter,
                                 game_mode_->volume_settings_parameter,
                                 pause);
  }
}

void Sound::PlayMine(EffectParameters explosion_parameters) {
  sounds_of_effects_.PlayMine(explosion_parameters.play,
                              explosion_parameters.volume_parameter,
                              game_mode_->volume_settings_parameter);
}

void Sound::PlayCarExplosion(EffectParameters explosion_parameters) {
  sounds_of_effects_.PlayCarExplosion(explosion_parameters.play,
                                      explosion_parameters.volume_parameter,
                                      game_mode_->volume_settings_parameter);
}

