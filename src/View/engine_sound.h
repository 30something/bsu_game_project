//#pragma once
//
//#include <QMediaPlayer>
//#include <QMediaPlaylist>
//#include <QWidget>
//
//#include "src/helpers/parameters_for_sounds.h"
//
//#include <vector>
//
//
//class Engine : public QWidget {
//    Q_OBJECT
//
// public:
//    explicit Engine(QWidget* parent = nullptr);
//    ~Engine() override = default;
//
//    void Play(const std::vector<EngineParameters>& engine_parameters, bool pause);
//    void PlayIdleSpeed(QMediaPlaylist* sound_playlist, QMediaPlayer* sound_player);
//    void PlayReversedEngine(QMediaPlaylist* sound_playlist, QMediaPlayer* sound_player);
//    void PlayEngine(QMediaPlaylist* sound_playlist, QMediaPlayer* sound_player);
//    void HandlingCases(QMediaPlaylist* sound_playlist, QMediaPlayer* sound_player,
//                       int int_speed_parameter, Motion motion_parameter);
//
//private:
////    QMediaPlaylist* sound_playlist_;
////    QMediaPlayer* sound_player_;
//    std::vector<QMediaPlaylist*> sound_playlists_;
//    std::vector<QMediaPlayer*> sound_players_;
//
//    static constexpr int kDefaultVolume = 30;
//    static constexpr int kIdleSpeedIndex = 0;
//    static constexpr int kMainEngineIndex = 1;
//    static constexpr int kReversedEngineIndex = 2;
//    static constexpr int kMainEngineLength = 2862;
//    static constexpr int kBackwardEngineLength = 1000;
//    static constexpr int kMaxReversedEnginePosition = 11000;
//};


#pragma once

#include <QMediaPlayer>
#include <QMediaPlaylist>
#include <QWidget>

#include "src/helpers/types_of_motion.h"

#include <vector>


class Engine : public QWidget {
 Q_OBJECT

 public:
    explicit Engine(QWidget* parent = nullptr, int index = 0);
    ~Engine() override = default;

    void Play(double speed_parameter, Motion motion_parameter, bool play, bool pause);
    void PlayIdleSpeed();
    void PlayReversedEngine();
    void PlayEngine();
    void HandlingCases(int int_speed_parameter, Motion motion_parameter);

 private:
    QMediaPlaylist* sound_playlist_;
    QMediaPlayer* sound_player_;
//    std::vector<QMediaPlayer*> sound_players_;
//    std::vector<QMediaPlaylist*> sound_playlists;

    static constexpr int kDefaultVolume = 30;
    static constexpr int kIdleSpeedIndex = 0;
    static constexpr int kMainEngineIndex = 1;
    static constexpr int kReversedEngineIndex = 2;
    static constexpr int kMainEngineLength = 2862;
    static constexpr int kBackwardEngineLength = 1000;
    static constexpr int kMaxReversedEnginePosition = 11000;
};