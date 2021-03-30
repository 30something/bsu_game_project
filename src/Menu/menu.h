#pragma once

#include <QLabel>
#include <QPushButton>
#include <QSize>
#include <QVBoxLayout>
#include <QWidget>

class Menu : public QWidget {
  Q_OBJECT

 public:
  explicit Menu(QWidget* parent = nullptr);
  ~Menu() override = default;

 signals:
  void StartButtonPressed();
  void SettingsButtonPressed();
  void ExitButtonPressed();

 private:
  void SetSizes();
  void SetUpLayout();
  void ConnectUI();

  QVBoxLayout* main_layout_ = nullptr;
  QLabel* name_label_ = nullptr;
  QPushButton* start_game_button_ = nullptr;
  QPushButton* settings_button_ = nullptr;
  QPushButton* credits_button_ = nullptr;
  QPushButton* exit_button_ = nullptr;
};
