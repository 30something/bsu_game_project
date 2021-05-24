#include "engine_sound.h"
#include <QDebug>

Engine::Engine(QWidget *parent, int volume_settings_parameter) :
        QWidget(parent),
        sound_playlist_(new QMediaPlaylist(this)),
        sound_player_(new QMediaPlayer(this)),
        volume_settings_parameter_(volume_settings_parameter) {
    sound_player_->setPlaylist(sound_playlist_);
    sound_player_->setVolume(kDefaultVolume);

    sound_playlist_->addMedia(
            QUrl("qrc:/resources/sounds/car_sounds/idle_speed.wav"));
    sound_playlist_->addMedia(
            QUrl("qrc:/resources/sounds/car_sounds/main_engine.wav"));
    sound_playlist_->addMedia(
            QUrl("qrc:/resources/sounds/car_sounds/reversed_engine.wav"));

    sound_playlist_->setPlaybackMode(QMediaPlaylist::CurrentItemInLoop);
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

    if (int_speed_parameter <= 5) {
        PlayIdleSpeed();
    } else if (motion_parameter == Motion::kWithoutMotion) {
        PlayReversedEngine();
    } else if (sound_playlist_->currentIndex() != kMainEngineIndex) {
        PlayEngine();
    }

    HandlingCases(int_speed_parameter, motion_parameter);
}

void Engine::PlayIdleSpeed() {
    if (sound_playlist_->currentIndex() != kIdleSpeedIndex) {
        sound_player_->stop();
        sound_playlist_->setCurrentIndex(kIdleSpeedIndex);
        sound_player_->play();
    }
}

void Engine::PlayEngine() {
    if (sound_playlist_->currentIndex() == kReversedEngineIndex) {
        int64_t position = sound_player_->position();
        sound_player_->stop();
        sound_playlist_->setCurrentIndex(kMainEngineIndex);
        sound_player_->setPosition(kMainEngineLength - (position / 4));
    } else {
        sound_player_->stop();
        sound_playlist_->setCurrentIndex(kMainEngineIndex);
    }
    sound_player_->play();
}

void Engine::PlayReversedEngine() {
    if (sound_playlist_->currentIndex() == kMainEngineIndex) {
        int64_t position = sound_player_->position();
        sound_player_->stop();
        sound_playlist_->setCurrentIndex(kReversedEngineIndex);
        int64_t reversed_position = 4 * (kMainEngineLength - position);
        if (reversed_position >= kMaxReversedEnginePosition) {
            PlayIdleSpeed();
            return;
        }
        sound_player_->setPosition(reversed_position);
        sound_player_->play();
    }
}

void Engine::HandlingCases(int int_speed_parameter, Motion motion_parameter) {
    if (sound_player_->position() >= kMaxReversedEnginePosition &&
        sound_playlist_->currentIndex() == kReversedEngineIndex) {
        PlayIdleSpeed();
    }

    if (sound_player_->position() >= kBackwardEngineLength &&
        motion_parameter == Motion::kBackwardMotion) {
        sound_player_->setPosition(sound_player_->position() - 200);
    }

    if (sound_playlist_->currentIndex() == kMainEngineIndex &&
        motion_parameter == Motion::kForwardMotion) {
        if (int_speed_parameter <= 30 &&
            sound_player_->position() >= kMainEngineLength / 3) {
            sound_player_->setPosition(sound_player_->position() - 200);
        } else if (int_speed_parameter <= 60 &&
                   sound_player_->position() >= 2 * kMainEngineLength / 3) {
            sound_player_->setPosition(sound_player_->position() - 200);
        }
        if (sound_player_->position() >= kMainEngineLength - 150) {
            sound_player_->setPosition(sound_player_->position() - 200);
        }
    }
}