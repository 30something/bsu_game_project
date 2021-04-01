#include "EngineSound.h"

Engine::Engine(QWidget* parent) : QWidget(parent),
                                  sound_playlist_(new QMediaPlaylist(this)),
                                  sound_player_(new QMediaPlayer(this)),
                                  volume_(kDefaultVolume) {
    sound_playlist_->
            addMedia(QUrl(
            "qrc:/resources/sounds/Engine_06.wav")
    );
    sound_player_->setPlaylist(sound_playlist_);
    sound_player_->setVolume(volume_);

    sound_playlist_->setPlaybackMode(QMediaPlaylist::CurrentItemInLoop);
    sound_player_->play();
}

void Engine::ChangeVolume(double coefficient) {
    double volume = 100 - kDefaultVolume;
    volume *= coefficient;
    volume_ = static_cast<int>(volume) + kDefaultVolume;
    sound_player_->setVolume(volume_);
}



