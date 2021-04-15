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
    QMediaPlayer* sound_player_;
    QMediaPlaylist* sound_playlist_;
    int volume_;
};
