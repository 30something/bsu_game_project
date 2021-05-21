#include "brake_sound.h"
#include <QDebug>

Brake::Brake(QWidget *parent) : QWidget(parent),
                                sound_playlist_(new QMediaPlaylist(this)),
                                sound_player_(new QMediaPlayer(this)) {
    sound_player_->setPlaylist(sound_playlist_);
    sound_playlist_->
            addMedia(QUrl(
            "qrc:/resources/sounds/car_sounds/car_brake.wav"));
    sound_playlist_->setPlaybackMode(QMediaPlaylist::CurrentItemOnce);
}

void Brake::Play(double speed_parameter, bool pause) {
    if (pause) {
        sound_player_->pause();
        return;
    }
    volume_ = static_cast<int>(100 * speed_parameter);
    if (volume_ > 0) {
        sound_player_->setVolume(volume_);
        sound_player_->play();
    } else {
        sound_player_->stop();
    }
}


