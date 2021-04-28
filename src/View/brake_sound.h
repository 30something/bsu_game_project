#pragma once

#include <QMediaPlayer>
#include <QMediaPlaylist>
#include <QWidget>


class Brake : public QWidget {
    Q_OBJECT

 public:
    explicit Brake(QWidget* parent = nullptr);
    ~Brake() override = default;

    void Play(double coefficient);
 private:
    QMediaPlaylist* sound_playlist_;
    QMediaPlayer* sound_player_;
    int volume_;
};
