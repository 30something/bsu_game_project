#pragma once

#include <QLabel>
#include <QPushButton>
#include <QSize>
#include <QSlider>
#include <QCheckBox>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QWidget>

#include "src/helpers/fonts.h"
#include "src/helpers/styles.h"
#include "src/helpers/sizes.h"
#include "src/helpers/game_mode.h"

class Settings : public QWidget {
  Q_OBJECT

 public:
  explicit Settings(GameMode* game_mode, QWidget* parent = nullptr);
  ~Settings() override = default;

 signals:
  void BackButtonPressed();
  void MakeFullScreen();
  void MakeDefaultScreenSize();

 private:
  void SetStyles();
  void SetUpLayout();
  void ConnectUI();

  void CommitSettingsChanges();

  QVBoxLayout* main_layout_;
  QHBoxLayout* music_layout_;
  QHBoxLayout* sound_layout_;
  QLabel* music_;
  QSlider* music_volume_;
  QLabel* sound_effects_;
  QSlider* sound_effects_volume_;
  QCheckBox* full_screen_cell_;
  QPushButton* apply_button_;
  QPushButton* back_button_;
  GameMode* game_mode_;
};
