#include "sounds_of_effects.h"
#include <QDebug>

void Effects::PlayBonus(bool is_playing) {
    if (is_playing) {
        QMediaPlayer *player = new QMediaPlayer;
        QMediaPlaylist *playlist = new QMediaPlaylist(player);
        player->setPlaylist(playlist);
        playlist->addMedia(QUrl(
                "qrc:/resources/sounds/effects/bonus.wav"));
        playlist->setPlaybackMode(QMediaPlaylist::CurrentItemOnce);
        player->play();
    }
}

void Effects::PlayMine(bool play_mine, double volume_parameter) {
    if (play_mine) {
        QMediaPlayer *player = new QMediaPlayer;
        QMediaPlaylist *playlist = new QMediaPlaylist(player);

        int volume = static_cast<int>(100 * volume_parameter);

        player->setPlaylist(playlist);
        player->setVolume(volume);
        playlist->addMedia(QUrl(
                "qrc:/resources/sounds/weapon/mine.wav"));
        playlist->setPlaybackMode(QMediaPlaylist::CurrentItemOnce);
        player->play();
    }
}

void Effects::PlayCarExplosion(bool play_car_explosion, double volume_parameter) {
    if (play_car_explosion) {
        QMediaPlayer *player = new QMediaPlayer;
        QMediaPlaylist *playlist = new QMediaPlaylist(player);

        int volume = static_cast<int>(100 * volume_parameter);

        player->setPlaylist(playlist);
        player->setVolume(volume);
        playlist->addMedia(QUrl(
                "qrc:/resources/sounds/effects/car_explosion.wav"));
        playlist->setPlaybackMode(QMediaPlaylist::CurrentItemOnce);
        player->play();
    }
}




