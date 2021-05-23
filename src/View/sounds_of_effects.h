#pragma once

#include <QMediaPlayer>
#include <QMediaPlaylist>

class Effects {

 public:
    Effects() = default;
    ~Effects() = default;

    void PlayBonus(bool play_bonus);
    void PlayMine(bool play_mine, double volume_parameter);
    void PlayCarExplosion(bool play_car_explosion, double volume_parameter);
};
