#include "EngineSound.h"
#include <QDebug>

Engine::Engine(QWidget* parent) : QWidget(parent),
                                  sound_playlist_(new QMediaPlaylist(this)),
                                  sound_player_(new QMediaPlayer(this)),
                                  volume_(kDefaultVolume) {
    sound_playlist_->
            addMedia(QUrl(
            "qrc:/resources/sounds/Engine_06.wav"));
    sound_playlist_->
            addMedia(QUrl(
            "qrc:/resources/sounds/BMW.wav"));
//    sound_playlist_->
//            addMedia(QUrl(
//            "qrc:/resources/sounds/CarEngineLoop3.wav"));
//    sound_playlist_->
//            addMedia(QUrl(
//            "qrc:/resources/sounds/New_engine.mp3"));
    sound_playlist_->setCurrentIndex(0);
    sound_player_->setPlaylist(sound_playlist_);
    sound_player_->setVolume(volume_);

    sound_playlist_->setPlaybackMode(QMediaPlaylist::CurrentItemOnce);
//    sound_player_->setPlaybackRate(0.75);
    sound_player_->play();
}

void Engine::ChangeVolume(double coefficient1) {
    int coefficient = (int)(10 * coefficient1);
    if (coefficient == 0 && sound_playlist_->currentIndex() != 0) {
        sound_playlist_->setCurrentIndex(0);
    } else if (coefficient > 0 && sound_playlist_->currentIndex() != 1) {
        sound_playlist_->setCurrentIndex(1);
        //sound_player_->setPosition((int)(coefficient * 2000));
    }
    if (coefficient > 0 && coefficient <= 2 && sound_player_->playbackRate() != 0.98) {
        sound_player_->setPlaybackRate(0.98);
    } else if (coefficient >= 4 && coefficient <= 6 && sound_player_->playbackRate() != 1) {
        sound_player_->setPlaybackRate(1);

    } else if (coefficient >= 8 && sound_player_->playbackRate() != 1.02) {
        sound_player_->setPlaybackRate(1.02);
    }
    int volume = 100 - kDefaultVolume;
    volume *= coefficient;
    volume_ = volume / 10 + kDefaultVolume;
    sound_player_->setVolume(volume_);
    sound_player_->play();
}



