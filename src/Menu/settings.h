#pragma once

#include <QLabel>
#include <QPushButton>
#include <QSize>
#include <QSlider>
#include <QCheckBox>
#include <QVBoxLayout>
#include <QWidget>

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
  void SetSizes();
  void SetUpLayout();
  void ConnectUI();

  void CommitSettingsChanges();

  QVBoxLayout* main_layout_;
  QLabel* music_;
  QSlider* music_volume_;
  QLabel* sound_effects_;
  QSlider* sound_effects_volume_;
  QCheckBox* full_screen_cell_;
  QPushButton* apply_button_;
  QPushButton* back_button_;
};
