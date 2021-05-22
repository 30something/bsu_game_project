//#include "engine_sound.h"
//#include <QDebug>
//
//Engine::Engine(QWidget *parent) : QWidget(parent),
////                                  sound_playlist_(new QMediaPlaylist(this)),
////                                  sound_player_(new QMediaPlayer(this)),
//                                  sound_playlists_(2, new QMediaPlaylist(this)),
//                                  sound_players_(2, new QMediaPlayer(this)) {
//    for (int i = 0; i < 2; i++) {
//        sound_players_.at(i)->setPlaylist(sound_playlists_.at(i));
//        sound_players_.at(i)->setVolume(kDefaultVolume);
//
//        std::string idle_speed_file = "qrc:/resources/sounds/car_sounds/idle_speed";
//        std::string main_engine_file = "qrc:/resources/sounds/car_sounds/main_engine";
//        std::string reversed_engine_file = "qrc:/resources/sounds/car_sounds/reversed_engine";
//
//        idle_speed_file += std::to_string(i) + ".wav";
//        main_engine_file += std::to_string(i) + ".wav";
//        reversed_engine_file += std::to_string(i) + ".wav";
//
//        sound_playlists_.at(i)->
//                addMedia(QUrl(
//                QString(idle_speed_file.c_str())));
//        sound_playlists_.at(i)->
//                addMedia(QUrl(
//                QString(main_engine_file.c_str())));
//        sound_playlists_.at(i)->addMedia(QUrl(
//                QString(reversed_engine_file.c_str())));
//
//        sound_playlists_.at(i)->setPlaybackMode(QMediaPlaylist::CurrentItemInLoop);
//        sound_players_.at(i)->setPlaybackRate(1);
//        sound_players_.at(i)->play();
//    }
//}
//
//void Engine::Play(const std::vector<EngineParameters>& engine_parameters, bool pause) {
//    for (int i = 0; i < 2; i++) {
//        qDebug() << i << " " << sound_playlists_.at(i)->currentIndex() << "\n";
//        int int_speed_parameter = static_cast<int>(100 * engine_parameters.at(i).speed_parameter);
//        Motion motion_parameter = engine_parameters.at(i).motion_parameter;
//        int volume = 100 - kDefaultVolume;
//        volume *= int_speed_parameter;
//        volume = (volume / 100) + kDefaultVolume;
//        sound_players_.at(i)->setVolume(volume);
//
//        if (motion_parameter == Motion::kIsDead) {
//            sound_players_.at(i)->stop();
//            continue;
//        }
//        if (pause) {
//            sound_players_.at(i)->pause();
//            continue;
//        }
//        sound_players_.at(i)->play();
//
//        if (int_speed_parameter <= 5) {
//            PlayIdleSpeed(sound_playlists_.at(i), sound_players_.at(i));
//        } else if (motion_parameter == Motion::kWithoutMotion) {
//            PlayReversedEngine(sound_playlists_.at(i), sound_players_.at(i));
//        } else if (sound_playlists_.at(i)->currentIndex() != kMainEngineIndex) {
//            PlayEngine(sound_playlists_.at(i), sound_players_.at(i));
//        }
//
//        HandlingCases(sound_playlists_.at(i), sound_players_.at(i),
//                      int_speed_parameter, motion_parameter);
//    }
//}
//
//void Engine::PlayIdleSpeed(QMediaPlaylist* sound_playlist, QMediaPlayer* sound_player) {
//    if (sound_playlist->currentIndex() != kIdleSpeedIndex) {
//        sound_player->stop();
//        sound_playlist->setCurrentIndex(kIdleSpeedIndex);
//        sound_player->play();
//    }
//}
//
//void Engine::PlayEngine(QMediaPlaylist* sound_playlist, QMediaPlayer* sound_player) {
//    if (sound_playlist->currentIndex() == kReversedEngineIndex) {
//        int64_t position = sound_player->position();
//        sound_player->stop();
//        sound_playlist->setCurrentIndex(kMainEngineIndex);
//        sound_player->setPosition(kMainEngineLength - (position / 4));
//    } else {
//        sound_player->stop();
//        sound_playlist->setCurrentIndex(kMainEngineIndex);
//    }
//    sound_player->play();
//}
//
//void Engine::PlayReversedEngine(QMediaPlaylist* sound_playlist, QMediaPlayer* sound_player) {
//    if (sound_playlist->currentIndex() == kMainEngineIndex) {
//        int64_t position = sound_player->position();
//        sound_player->stop();
//        sound_playlist->setCurrentIndex(kReversedEngineIndex);
//        int64_t reversed_position = 4 * (kMainEngineLength - position);
//        if (reversed_position >= kMaxReversedEnginePosition) {
//            PlayIdleSpeed(sound_playlist, sound_player);
//            return;
//        }
//        sound_player->setPosition(reversed_position);
//        sound_player->play();
//    }
//}
//
//void Engine::HandlingCases(QMediaPlaylist* sound_playlist, QMediaPlayer* sound_player,
//                           int int_speed_parameter, Motion motion_parameter) {
//    if (sound_player->position() >= kMaxReversedEnginePosition &&
//        sound_playlist->currentIndex() == kReversedEngineIndex) {
//        PlayIdleSpeed(sound_playlist, sound_player);
//    }
//
//    if (sound_player->position() >= kBackwardEngineLength &&
//        motion_parameter == Motion::kBackwardMotion) {
//        sound_player->setPosition(sound_player->position() - 200);
//    }
//
//    if (sound_playlist->currentIndex() == kMainEngineIndex &&
//        motion_parameter == Motion::kForwardMotion) {
//        if (int_speed_parameter <= 30 &&
//            sound_player->position() >= kMainEngineLength / 3) {
//            sound_player->setPosition(sound_player->position() - 200);
//        } else if (int_speed_parameter <= 60 &&
//                   sound_player->position() >= 2 * kMainEngineLength / 3) {
//            sound_player->setPosition(sound_player->position() - 200);
//        }
//        if (sound_player->position() >= kMainEngineLength - 150) {
//            sound_player->setPosition(sound_player->position() - 200);
//        }
//    }
//}
//
//
//
#include "engine_sound.h"
#include <QDebug>

Engine::Engine(QWidget *parent, int index) : QWidget(parent),
                                  sound_playlist_(new QMediaPlaylist(this)),
                                  sound_player_(new QMediaPlayer(this)) {
    sound_player_->setPlaylist(sound_playlist_);
    sound_player_->setVolume(kDefaultVolume);

    std::string idle_speed_file =
            "qrc:/resources/sounds/car_sounds/idle_speed/idle_speed" +
            std::to_string(index) + ".wav";
    std::string main_engine_file =
            "qrc:/resources/sounds/car_sounds/main_engine/main_engine" +
            std::to_string(index) + ".wav";
    std::string reversed_engine_file =
            "qrc:/resources/sounds/car_sounds/reversed_engine/reversed_engine" +
            std::to_string(index) + ".wav";

    sound_playlist_->addMedia(QUrl(QString(idle_speed_file.c_str())));
    sound_playlist_->addMedia(QUrl(QString(main_engine_file.c_str())));
    sound_playlist_->addMedia(QUrl(QString(reversed_engine_file.c_str())));

    sound_playlist_->setPlaybackMode(QMediaPlaylist::CurrentItemInLoop);
    sound_player_->setPlaybackRate(1);
    sound_player_->play();
}

void Engine::Play(double speed_parameter, Motion motion_parameter, bool play, bool pause) {
    if (!play) {
        sound_player_->stop();
        return;
    }
    if (motion_parameter == Motion::kIsDead) {
        sound_player_->stop();
        return;
    }
    if (pause) {
        sound_player_->pause();
        return;
    }

    int int_speed_parameter = static_cast<int>(100 * speed_parameter);
    int volume = 100 - kDefaultVolume;
    volume *= int_speed_parameter;
    volume = (volume / 100) + kDefaultVolume;
    sound_player_->setVolume(volume);
    sound_player_->play();

    if (int_speed_parameter <= 5) {
        PlayIdleSpeed();
    } else if (motion_parameter == Motion::kWithoutMotion) {
        PlayReversedEngine();
    } else if (sound_playlist_->currentIndex() != kMainEngineIndex) {
        PlayEngine();
    }

    HandlingCases(int_speed_parameter, motion_parameter);
}

void Engine::PlayIdleSpeed() {
    if (sound_playlist_->currentIndex() != kIdleSpeedIndex) {
        sound_player_->stop();
        sound_playlist_->setCurrentIndex(kIdleSpeedIndex);
        sound_player_->play();
    }
}

void Engine::PlayEngine() {
    if (sound_playlist_->currentIndex() == kReversedEngineIndex) {
        int64_t position = sound_player_->position();
        sound_player_->stop();
        sound_playlist_->setCurrentIndex(kMainEngineIndex);
        sound_player_->setPosition(kMainEngineLength - (position / 4));
    } else {
        sound_player_->stop();
        sound_playlist_->setCurrentIndex(kMainEngineIndex);
    }
    sound_player_->play();
}

void Engine::PlayReversedEngine() {
    if (sound_playlist_->currentIndex() == kMainEngineIndex) {
        int64_t position = sound_player_->position();
        sound_player_->stop();
        sound_playlist_->setCurrentIndex(kReversedEngineIndex);
        int64_t reversed_position = 4 * (kMainEngineLength - position);
        if (reversed_position >= kMaxReversedEnginePosition) {
            PlayIdleSpeed();
            return;
        }
        sound_player_->setPosition(reversed_position);
        sound_player_->play();
    }
}

void Engine::HandlingCases(int int_speed_parameter, Motion motion_parameter) {
    if (sound_player_->position() >= kMaxReversedEnginePosition &&
        sound_playlist_->currentIndex() == kReversedEngineIndex) {
        PlayIdleSpeed();
    }

    if (sound_player_->position() >= kBackwardEngineLength &&
        motion_parameter == Motion::kBackwardMotion) {
        sound_player_->setPosition(sound_player_->position() - 200);
    }

    if (sound_playlist_->currentIndex() == kMainEngineIndex &&
        motion_parameter == Motion::kForwardMotion) {
        if (int_speed_parameter <= 30 &&
            sound_player_->position() >= kMainEngineLength / 3) {
            sound_player_->setPosition(sound_player_->position() - 200);
        } else if (int_speed_parameter <= 60 &&
                   sound_player_->position() >= 2 * kMainEngineLength / 3) {
            sound_player_->setPosition(sound_player_->position() - 200);
        }
        if (sound_player_->position() >= kMainEngineLength - 150) {
            sound_player_->setPosition(sound_player_->position() - 200);
        }
    }
}