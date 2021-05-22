#include "brake_sound.h"
#include <QDebug>

Brake::Brake(QWidget *parent, int index) : QWidget(parent),
                                sound_playlist_(new QMediaPlaylist(this)),
                                sound_player_(new QMediaPlayer(this)) {
    sound_player_->setPlaylist(sound_playlist_);

    std::string brake_file =
            "qrc:/resources/sounds/car_sounds/car_brake/car_brake" +
            std::to_string(index) + ".wav";

    sound_playlist_->addMedia(QUrl(QString(brake_file.c_str())));

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


