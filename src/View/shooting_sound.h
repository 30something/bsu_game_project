#pragma once

#include <QMediaPlayer>
#include <QMediaPlaylist>
#include <QWidget>


class Shooting : public QWidget {
    Q_OBJECT

 public:
    explicit Shooting(QWidget* parent = nullptr);
    ~Shooting() override = default;

    void Play(bool using_gun, bool bullets, bool enable_weapons,
                        double volume_parameter, int volume_settings_parameter,
                        bool pause);
 private:
    QMediaPlayer* sound_player_;
    QMediaPlaylist* sound_playlist_;
    int volume_settings_parameter_;
};
