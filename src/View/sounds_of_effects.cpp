#include "sounds_of_effects.h"

Effects::Effects(QWidget* parent) : QWidget(parent) {}

void Effects::PlayBonus(bool is_playing,
                        int volume_settings_parameter) {
    if (is_playing) {
        QMediaPlayer *player = new QMediaPlayer(this);
        QMediaPlaylist *playlist = new QMediaPlaylist(player);

        volume_settings_parameter_ = volume_settings_parameter;
        int volume = volume_settings_parameter_;

        player->setPlaylist(playlist);
        player->setVolume(volume);
        playlist->addMedia(QUrl(
                "qrc:/resources/sounds/effects/bonus.wav"));
        playlist->setPlaybackMode(QMediaPlaylist::CurrentItemOnce);
        player->play();
    }
}

void Effects::PlayMine(bool play_mine, double volume_parameter,
                       int volume_settings_parameter) {
    if (play_mine) {
        QMediaPlayer *player = new QMediaPlayer(this);
        QMediaPlaylist *playlist = new QMediaPlaylist(player);

        int volume = static_cast<int>(100 * volume_parameter);
        volume_settings_parameter_ = volume_settings_parameter;
        volume *= volume_settings_parameter_;
        volume /= 100;

        player->setPlaylist(playlist);
        player->setVolume(volume);
        playlist->addMedia(QUrl(
                "qrc:/resources/sounds/weapon/mine.wav"));
        playlist->setPlaybackMode(QMediaPlaylist::CurrentItemOnce);
        player->play();
    }
}

void
Effects::PlayCarExplosion(bool play_car_explosion, double volume_parameter,
                          int volume_settings_parameter) {
    if (play_car_explosion) {
        QMediaPlayer *player = new QMediaPlayer(this);
        QMediaPlaylist *playlist = new QMediaPlaylist(player);

        int volume = static_cast<int>(100 * volume_parameter);
        volume_settings_parameter_ = volume_settings_parameter;
        volume *= volume_settings_parameter_;
        volume /= 100;

        player->setPlaylist(playlist);
        player->setVolume(volume);
        playlist->addMedia(QUrl(
                "qrc:/resources/sounds/effects/car_explosion.wav"));
        playlist->setPlaybackMode(QMediaPlaylist::CurrentItemOnce);
        player->play();
    }
}




