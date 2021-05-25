#pragma once

#include <QLabel>
#include <QPushButton>
#include <QSize>
#include <QVBoxLayout>
#include <QWidget>

#include "src/helpers/sizes.h"
#include "src/helpers/fonts.h"
#include "src/helpers/styles.h"

class Menu : public QWidget {
 Q_OBJECT

 public:
  explicit Menu(QWidget* parent = nullptr);
  ~Menu() override = default;

 signals:
  void SinglePlayerPressed();
  void MultiPlayerPressed();
  void SettingsButtonPressed();
  void ExitButtonPressed();

 private:
  void SetStyles();
  void SetUpLayout();
  void ConnectUI();

  QVBoxLayout* main_layout_ = nullptr;
  QLabel* name_label_ = nullptr;
  QPushButton* single_player_button_ = nullptr;
  QPushButton* multi_player_button_ = nullptr;
  QPushButton* settings_button_ = nullptr;
  QPushButton* credits_button_ = nullptr;
  QPushButton* exit_button_ = nullptr;
};
