#pragma once

#include <QMediaPlayer>
#include <QMediaPlaylist>
#include <QWidget>


class Drift : public QWidget {
    Q_OBJECT

 public:
    explicit Drift(QWidget* parent = nullptr);
    ~Drift() override = default;

    void Play(double speed_parameter, bool car_is_alive, double volume_parameter, bool pause);
 private:
    QMediaPlaylist* sound_playlist_;
    QMediaPlayer* sound_player_;
};
