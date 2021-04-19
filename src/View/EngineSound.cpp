#include "EngineSound.h"
#include <QDebug>

Engine::Engine(QWidget* parent) : QWidget(parent),
                                  sound_playlist_(new QMediaPlaylist(this)),
                                  sound_player_(new QMediaPlayer(this)),
                                  volume_(kDefaultVolume) {
    sound_player_->setPlaylist(sound_playlist_);
    sound_player_->setVolume(volume_);
    sound_playlist_->
            addMedia(QUrl(
            "qrc:/resources/sounds/IdleSpeed.wav"));
    sound_playlist_->
            addMedia(QUrl(
            "qrc:/resources/sounds/BMW.wav"));
    sound_playlist_->addMedia(QUrl(
            "qrc:/resources/sounds/BMW (reversed changed).wav"));

    sound_playlist_->setPlaybackMode(QMediaPlaylist::CurrentItemInLoop);
    sound_player_->setPlaybackRate(1);
    sound_player_->play();
}

//TODO fix engine sound

void Engine::Play(double coefficient1, int direction, bool car_is_alive) {
    if (!car_is_alive) {
        sound_player_->stop();
        return;
    }

    int coefficient = (int)(100 * coefficient1);

//    bool reversed_playing = false;

//    if (coefficient < 0) {
//        reversed_playing = true;
//        coefficient *= -1;
//    }

    int volume = 100 - kDefaultVolume;
    volume *= coefficient;
    volume_ = (volume / 100) + kDefaultVolume;
    sound_player_->setVolume(volume_);

    if (coefficient <= 5) {
        PlayIdleSpeed();
    } else if (coefficient >= 10 && direction == 0) {
        PlayReversedEngine();
    } else if (coefficient >= 10 && sound_playlist_->currentIndex() != 1) {
        PlayEngine();
    }

    if (sound_player_->position() >= 1000 && direction == -1) {
        sound_player_->setPosition(sound_player_->position() - 200);
    }
//    }
//    } else if (coefficient >= 98 && sound_playlist_->currentIndex() == 1) {
//        int64_t position = sound_player_->position();
//        sound_playlist_->setCurrentIndex(3);
//        sound_player_->setPosition(position);
//    }

//    if (coefficient > 10 && coefficient <= 20) {
//        if (sound_player_->playbackRate() != 0.98) {
//            sound_player_->setPlaybackRate(0.98);
//        }
//    } else
//        if (coefficient >= 40 && coefficient <= 60) {
//        if (sound_player_->playbackRate() != 1) {
//            sound_player_->setPlaybackRate(1);
//        }
//    } else if (coefficient >= 80) {
////        if (sound_playlist_->currentIndex() == 1 && sound_player_->position() >= 2700) {
////            sound_player_->setPosition(2400);
////        }
//        if (sound_player_->playbackRate() != 1.02) {
//            sound_player_->setPlaybackRate(1.02);
//        }
//    }

//    sound_player_->play();
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



