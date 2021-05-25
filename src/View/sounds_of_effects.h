#pragma once

#include <QMediaPlayer>
#include <QMediaPlaylist>
#include <QWidget>

class Effects : public QWidget {
 Q_OBJECT
 public:
  explicit Effects(QWidget* parent = nullptr);
  ~Effects() override = default;

  void PlayBonus(bool play_bonus, int volume_settings_parameter);
  void PlayMine(bool play_mine, double volume_parameter,
                int volume_settings_parameter);
  void PlayCarExplosion(bool play_car_explosion, double volume_parameter,
                        int volume_settings_parameter);

 private:
  int volume_settings_parameter_;
};
