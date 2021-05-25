#pragma once

#include <vector>

#include <QMediaPlayer>
#include <QMediaPlaylist>
#include <QWidget>

#include "src/helpers/types_of_motion.h"

class Engine : public QWidget {
  Q_OBJECT

 public:
  explicit Engine(QWidget* parent = nullptr,
                  int volume_settings_parameter = 0);
  ~Engine() override = default;

  void Play(double speed_parameter, Motion motion_parameter,
            double volume_parameter, int volume_settings_parameter,
            bool pause);

 private:
  QMediaPlaylist* sound_playlist_;
  QMediaPlayer* sound_player_;
  int volume_settings_parameter_;

  static constexpr int kDefaultVolume = 10;
};
