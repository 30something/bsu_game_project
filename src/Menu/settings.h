#pragma once

#include <QLabel>
#include <QPushButton>
#include <QSize>
#include <QSlider>
#include <QRadioButton>
#include <QVBoxLayout>
#include <QWidget>

class Settings : public QWidget {
  Q_OBJECT

 public:
  explicit Settings(QWidget* parent = nullptr);
  ~Settings() override = default;

 signals:
  void BackButtonPressed();

 private:
  QVBoxLayout* main_layout_;
  QLabel* music_;
  QSlider* music_volume_;
  QLabel* sound_effects_;
  QSlider* sound_effects_volume_;
  QRadioButton* full_screen_cell_;
  QPushButton* back_button_;
};
