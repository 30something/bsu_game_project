#pragma once

#include <QMediaPlayer>
#include <QMediaPlaylist>
#include <QWidget>


class Drift : public QWidget {
    Q_OBJECT

 public:
    explicit Drift(QWidget* parent = nullptr);
    ~Drift() override = default;

    void Play(double coefficient);
 private:
    QMediaPlaylist* sound_playlist_;
    QMediaPlayer* sound_player_;
    int volume_;
};
