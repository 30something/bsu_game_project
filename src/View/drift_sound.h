#pragma once

#include <QMediaPlayer>
#include <QMediaPlaylist>
#include <QWidget>


class Drift : public QWidget {
    Q_OBJECT

 public:
    explicit Drift(QWidget* parent = nullptr, int index = 0);
    ~Drift() override = default;

    void Play(double speed_parameter, bool car_is_alive, bool pause);
 private:
    QMediaPlaylist* sound_playlist_;
    QMediaPlayer* sound_player_;
    int volume_ = 0;
};
