#pragma once

#include <QMediaPlayer>
#include <QMediaPlaylist>
#include <QWidget>


class Effects : public QWidget {
    Q_OBJECT

 public:
    explicit Effects(QWidget* parent = nullptr);
    ~Effects() override = default;

    void PlayBonus(bool play_bonus);
    void PlayShooting(bool using_gun, bool bullets);
    void PlayMine(bool play_mine);
    void PlayCarExplosion(bool play_car_explosion);
 private:
    QMediaPlayer* sound_player_;
    QMediaPlaylist* sound_playlist_;
};
