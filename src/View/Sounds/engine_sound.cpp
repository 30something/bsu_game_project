#include "engine_sound.h"

Engine::Engine(QWidget* parent, int volume_settings_parameter) :
    QWidget(parent),
    sound_playlist_(new QMediaPlaylist(this)),
    sound_player_(new QMediaPlayer(this)),
    volume_settings_parameter_(volume_settings_parameter) {
  sound_player_->setPlaylist(sound_playlist_);
  sound_player_->setVolume(kDefaultVolume);

  sound_playlist_->addMedia(
      QUrl("qrc:/resources/sounds/car_sounds/engine.wav"));
  sound_playlist_->setPlaybackMode(QMediaPlaylist::CurrentItemInLoop);
  sound_playlist_->setCurrentIndex(0);
}

void Engine::Play(double speed_parameter, Motion motion_parameter,
                  double volume_parameter, int volume_settings_parameter,
                  bool pause) {
  if (motion_parameter == Motion::kIsDead) {
    sound_player_->stop();
    return;
  }
  if (pause) {
    sound_player_->pause();
    return;
  }
  int int_speed_parameter = static_cast<int>(100 * speed_parameter);
  int volume = 100 - kDefaultVolume;
  volume *= int_speed_parameter;
  volume = (volume / 100) + kDefaultVolume;

  volume *= static_cast<int>(100 * volume_parameter);
  volume /= 100;

  volume_settings_parameter_ = volume_settings_parameter;
  volume *= volume_settings_parameter_;
  volume /= 100;

  sound_player_->setVolume(volume);
  sound_player_->play();
  if (sound_player_->position() > sound_player_->duration() / 10 * 9) {
    sound_player_->setPosition(0);
  }
}
