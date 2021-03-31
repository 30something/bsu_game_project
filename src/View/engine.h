#pragma once

#include <QMediaPlayer>
#include <QMediaPlaylist>
#include <QWidget>


class Engine : public QWidget {
public:
    explicit Engine(QWidget* parent = nullptr);
    ~Engine() override = default;

    void ChangeVolume(double coefficient);
private:
    QMediaPlaylist* sound_playlist_;
    QMediaPlayer* sound_player_;
    static constexpr int kDefaultVolume = 5;
    int volume_;
};
