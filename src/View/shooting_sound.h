#pragma once

#include <QMediaPlayer>
#include <QMediaPlaylist>
#include <QWidget>


class Shooting : public QWidget {
 Q_OBJECT

 public:
    explicit Shooting(QWidget* parent = nullptr, int index = 0);
    ~Shooting() override = default;

    void Play(bool using_gun, bool bullets, bool enable_weapons, bool pause);
 private:
    QMediaPlayer* sound_player_;
    QMediaPlaylist* sound_playlist_;
};
