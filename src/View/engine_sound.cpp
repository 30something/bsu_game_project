#include "engine_sound.h"
#include <QDebug>

Engine::Engine(QWidget *parent) : QWidget(parent),
                                  sound_playlist_(new QMediaPlaylist(this)),
                                  sound_player_(new QMediaPlayer(this)),
                                  volume_(kDefaultVolume) {
    sound_player_->setPlaylist(sound_playlist_);
    sound_player_->setVolume(volume_);
    sound_playlist_->
            addMedia(QUrl(
            "qrc:/resources/sounds/car_sounds/idle_speed.wav"));
    sound_playlist_->
            addMedia(QUrl(
            "qrc:/resources/sounds/car_sounds/main_engine.wav"));
    sound_playlist_->addMedia(QUrl(
            "qrc:/resources/sounds/car_sounds/reversed_engine.wav"));

    sound_playlist_->setPlaybackMode(QMediaPlaylist::CurrentItemInLoop);
    sound_player_->setPlaybackRate(1);
    sound_player_->play();
}

void Engine::Play(double coefficient1, int direction, bool car_is_alive) {
    if (!car_is_alive) {
        sound_player_->stop();
        return;
    }

    int coefficient = static_cast<int>(100 * coefficient1);

    int volume = 100 - kDefaultVolume;
    volume *= coefficient;
    volume_ = (volume / 100) + kDefaultVolume;
    sound_player_->setVolume(volume_);

    if (coefficient <= 5) {
        PlayIdleSpeed();
    } else if (direction == 0) {
        PlayReversedEngine();
    } else if (sound_playlist_->currentIndex() != 1) {
        PlayEngine();
    }

    if (sound_player_->position() >= 1000 && direction == -1) {
        sound_player_->setPosition(sound_player_->position() - 200);
    }
    if (sound_playlist_->currentIndex() == 1 && direction == 1) {
        if (coefficient <= 30 && sound_player_->position() >= 981) {
            sound_player_->setPosition(sound_player_->position() - 200);
        } else if (coefficient <= 60 && sound_player_->position() >= 1962) {
            sound_player_->setPosition(sound_player_->position() - 200);
        }
        if (sound_player_->position() >= 2700) {
            sound_player_->setPosition(sound_player_->position() - 120);
        }
    }
}

void Engine::PlayIdleSpeed() {
    if (sound_playlist_->currentIndex() != 0) {
        sound_player_->stop();
        sound_playlist_->setCurrentIndex(0);
        sound_player_->play();
    }
}

void Engine::PlayEngine() {
    if (sound_playlist_->currentIndex() == 2) {
        int64_t position = sound_player_->position();
        sound_player_->stop();
        sound_playlist_->setCurrentIndex(1);
        sound_player_->setPosition(2862 - (position / 4));
    } else {
        sound_player_->stop();
        sound_playlist_->setCurrentIndex(1);
    }
    sound_player_->play();
}

void Engine::PlayReversedEngine() {
    if (sound_playlist_->currentIndex() == 1) {
        int64_t position = sound_player_->position();
        sound_player_->stop();
        sound_playlist_->setCurrentIndex(2);
        sound_player_->setPosition(4 * (2862 - position));
        sound_player_->play();
    }
}



