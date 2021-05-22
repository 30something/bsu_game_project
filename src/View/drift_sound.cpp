#include "drift_sound.h"
#include <QDebug>

Drift::Drift(QWidget *parent, int index) : QWidget(parent),
                                sound_playlist_(new QMediaPlaylist(this)),
                                sound_player_(new QMediaPlayer(this)) {
    sound_player_->setPlaylist(sound_playlist_);

    std::string drift_file =
            "qrc:/resources/sounds/car_sounds/drift/drift" +
            std::to_string(index) + ".wav";
    std::string drift_loop_file =
            "qrc:/resources/sounds/car_sounds/drift_loop/drift_loop" +
            std::to_string(index) + ".wav";

    sound_playlist_->addMedia(QUrl(QString(drift_file.c_str())));
    sound_playlist_->addMedia(QUrl(QString(drift_loop_file.c_str())));

    sound_playlist_->setPlaybackMode(QMediaPlaylist::CurrentItemInLoop);
}

void Drift::Play(double speed_parameter, bool enable_drifting, bool pause) {
    if (!enable_drifting) {
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
