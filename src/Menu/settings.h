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

class Settings : public QWidget {
  Q_OBJECT

 public:
  explicit Settings(QWidget* parent = nullptr);
  ~Settings() override = default;

 signals:
  void BackButtonPressed();
  void MakeFullScreen();
  void MakeDefaultScreenSize();

 private:
  void SetFonts();
  void SetSizes();
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
};
