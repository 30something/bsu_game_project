#pragma once

#include <QMediaPlayer>
#include <QMediaPlaylist>
#include <QWidget>


class Engine : public QWidget {
    Q_OBJECT

 public:
    explicit Engine(QWidget* parent = nullptr);
    ~Engine() override = default;

    void Play(double coefficient, int direction, bool car_is_alive);
    void PlayIdleSpeed();
    void PlayReversedEngine();
    void PlayEngine();

 private:
    QMediaPlaylist* sound_playlist_;
    QMediaPlayer* sound_player_;
    static constexpr int kDefaultVolume = 30;
    int volume_;
};
