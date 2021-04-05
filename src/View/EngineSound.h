#pragma once

#include <QMediaPlayer>
#include <QMediaPlaylist>
#include <QWidget>


class Engine : public QWidget {
    Q_OBJECT

 public:
    explicit Engine(QWidget* parent = nullptr);
    ~Engine() override = default;

    void ChangeVolume(double coefficient);
 private:
    QMediaPlaylist* sound_playlist_;
    QMediaPlayer* sound_player_;
    static constexpr int kDefaultVolume = 10;
    int volume_;
};
