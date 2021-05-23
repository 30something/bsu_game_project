#pragma once

#include <QMediaPlayer>
#include <QMediaPlaylist>
#include <QWidget>

#include "src/helpers/types_of_motion.h"

#include <vector>


class Engine : public QWidget {
    Q_OBJECT

 public:
    explicit Engine(QWidget* parent = nullptr);
    ~Engine() override = default;

    void Play(double speed_parameter, Motion motion_parameter, double volume_parameter, bool pause);
    void PlayIdleSpeed();
    void PlayReversedEngine();
    void PlayEngine();
    void HandlingCases(int int_speed_parameter, Motion motion_parameter);

 private:
    QMediaPlaylist* sound_playlist_;
    QMediaPlayer* sound_player_;

    static constexpr int kDefaultVolume = 30;
    static constexpr int kIdleSpeedIndex = 0;
    static constexpr int kMainEngineIndex = 1;
    static constexpr int kReversedEngineIndex = 2;
    static constexpr int kMainEngineLength = 2862;
    static constexpr int kBackwardEngineLength = 1000;
    static constexpr int kMaxReversedEnginePosition = 11000;
};