#pragma once

#include <QMediaPlayer>
#include <QMediaPlaylist>
#include <QWidget>


class Brake : public QWidget {
    Q_OBJECT

 public:
    explicit Brake(QWidget* parent = nullptr);
    ~Brake() override = default;

    void Play(double speed_parameter, double volume_parameter, bool pause);
 private:
    QMediaPlaylist* sound_playlist_;
    QMediaPlayer* sound_player_;
};
