#include "shooting_sound.h"

Shooting::Shooting(QWidget *parent, int index) : QWidget(parent),
                                               sound_player_(new QMediaPlayer(this)),
                                               sound_playlist_(new QMediaPlaylist(this)) {
    sound_player_->setPlaylist(sound_playlist_);

    std::string gunshot_file =
            "qrc:/resources/sounds/weapon/gunshot_sound/gunshot_sound" +
            std::to_string(index) + ".wav";
    std::string no_bullets_file =
            "qrc:/resources/sounds/weapon/no_bullets/no_bullets" +
            std::to_string(index) + ".wav";

    sound_playlist_->addMedia(QUrl(QString(gunshot_file.c_str())));
    sound_playlist_->addMedia(QUrl(QString(no_bullets_file.c_str())));
}

void Shooting::Play(bool using_gun, bool bullets, bool enable_weapons, bool pause) {
    if (!enable_weapons) {
        sound_player_->stop();
        return;
    }
    if (pause) {
        sound_player_->pause();
        return;
    }
    if (using_gun) {
        if (bullets && !(sound_playlist_->currentIndex() == 0 &&
                         sound_player_->state() ==
                         QMediaPlayer::PlayingState)) {
            sound_playlist_->setPlaybackMode(
                    QMediaPlaylist::CurrentItemInLoop);
            sound_player_->stop();
            sound_playlist_->setCurrentIndex(0);
        } else if (!bullets && !(sound_playlist_->currentIndex() == 1 &&
                                 sound_player_->state() ==
                                 QMediaPlayer::PlayingState)) {
            sound_playlist_->setPlaybackMode(
                    QMediaPlaylist::CurrentItemOnce);
            sound_player_->stop();
            sound_playlist_->setCurrentIndex(1);
        }
        sound_player_->play();
    } else if (sound_playlist_->currentIndex() != 1) {
        sound_player_->stop();
    }
}