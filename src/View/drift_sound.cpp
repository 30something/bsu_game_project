#include "drift_sound.h"
#include <QDebug>

Drift::Drift(QWidget *parent) : QWidget(parent),
                                sound_playlist_(new QMediaPlaylist(this)),
                                sound_player_(new QMediaPlayer(this)) {
    sound_player_->setPlaylist(sound_playlist_);
    sound_playlist_->
            addMedia(QUrl(
            "qrc:/resources/sounds/car_sounds/drift.wav"));
    sound_playlist_->
            addMedia(QUrl(
            "qrc:/resources/sounds/car_sounds/drift_loop.wav"));
    sound_playlist_->setPlaybackMode(QMediaPlaylist::CurrentItemInLoop);
}

void Drift::Play(double speed_parameter, bool car_is_alive, bool pause) {
    if (!car_is_alive) {
        sound_player_->stop();
        return;
    }
    if (pause) {
        sound_player_->pause();
        return;
    }

    volume_ = static_cast<int>(100 * speed_parameter);
    sound_player_->setVolume(volume_);

    if (volume_ > 0) {
        sound_player_->play();
    } else {
        if (sound_playlist_->currentIndex() != 0) {
            sound_playlist_->setCurrentIndex(0);
        }
        sound_player_->stop();
    }
    if (sound_player_->position() >= 2650 &&
        sound_playlist_->currentIndex() == 0) {
        sound_player_->stop();
        sound_playlist_->setCurrentIndex(1);
        sound_player_->play();
    }
}
