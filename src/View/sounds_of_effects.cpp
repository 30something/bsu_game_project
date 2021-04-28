#include "sounds_of_effects.h"
#include <QDebug>

Effects::Effects(QWidget *parent) : QWidget(parent),
                                    sound_player_(new QMediaPlayer(this)),
                                    sound_playlist_(new QMediaPlaylist(this)) {
    sound_player_->setPlaylist(sound_playlist_);
    sound_playlist_->
            addMedia(QUrl(
            "qrc:/resources/sounds/weapon/gunshot_sound.wav"));
    sound_playlist_->
            addMedia(QUrl(
            "qrc:/resources/sounds/weapon/no_bullets.wav"));
}

void Effects::PlayBonus(bool play_bonus) {
    if (play_bonus) {
        QMediaPlayer *player = new QMediaPlayer(this);
        QMediaPlaylist *playlist = new QMediaPlaylist(player);
        player->setPlaylist(playlist);
        playlist->addMedia(QUrl("qrc:/resources/sounds/effects/bonus.wav"));
        playlist->setPlaybackMode(QMediaPlaylist::CurrentItemOnce);
        player->play();
    }
}

void Effects::PlayShooting(bool using_gun, bool bullets) {
    if (using_gun) {
        if (bullets && !(sound_playlist_->currentIndex() == 0 && sound_player_->state()
                                                                 == QMediaPlayer::PlayingState)) {
            sound_playlist_->setPlaybackMode(QMediaPlaylist::CurrentItemInLoop);
            sound_playlist_->setCurrentIndex(0);
            sound_player_->play();
        } else if (!bullets && !(sound_playlist_->currentIndex() == 1 && sound_player_->state()
                                                                            == QMediaPlayer::PlayingState)) {
            sound_playlist_->setPlaybackMode(QMediaPlaylist::CurrentItemOnce);
            sound_playlist_->setCurrentIndex(1);
            sound_player_->play();
        }
    } else if (sound_playlist_->currentIndex() != 1) {
        sound_player_->stop();
    }
}

void Effects::PlayMine(bool play_mine) {
    if (play_mine) {
        QMediaPlayer *player = new QMediaPlayer(this);
        QMediaPlaylist *playlist = new QMediaPlaylist(player);
        player->setPlaylist(playlist);
        playlist->addMedia(QUrl("qrc:/resources/sounds/weapon/mine.wav"));
        playlist->setPlaybackMode(QMediaPlaylist::CurrentItemOnce);
        player->play();
    }
}

void Effects::PlayCarExplosion(bool play_car_explosion) {
    if (play_car_explosion) {
        QMediaPlayer *player = new QMediaPlayer(this);
        QMediaPlaylist *playlist = new QMediaPlaylist(player);
        player->setPlaylist(playlist);
        playlist->addMedia(QUrl("qrc:/resources/sounds/effects/car_explosion.wav"));
        playlist->setPlaybackMode(QMediaPlaylist::CurrentItemOnce);
        player->play();
    }
}




