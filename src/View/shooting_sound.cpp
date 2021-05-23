#include "shooting_sound.h"

Shooting::Shooting(QWidget *parent) : QWidget(parent),
                                               sound_player_(new QMediaPlayer(this)),
                                               sound_playlist_(new QMediaPlaylist(this)) {
    sound_player_->setPlaylist(sound_playlist_);

    sound_playlist_->addMedia(QUrl("qrc:/resources/sounds/weapon/gunshot_sound.wav"));
    sound_playlist_->addMedia(QUrl("qrc:/resources/sounds/weapon/no_bullets.wav"));
}

void Shooting::Play(bool using_gun, bool bullets, bool enable_weapons,
                    double volume_parameter, bool pause) {
    if (!enable_weapons) {
        sound_player_->stop();
        return;
    }
    if (pause) {
        sound_player_->pause();
        return;
    }

    int volume = static_cast<int>(100 * volume_parameter);

    sound_player_->setVolume(volume);

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