#pragma once

#include <QGridLayout>
#include <QLabel>
#include <QPushButton>
#include <QSize>
#include <QWidget>

#include "src/helpers/sizes.h"
#include "src/helpers/fonts.h"

class SmallExitWindow : public QWidget {
  Q_OBJECT

 public:
  explicit SmallExitWindow(QWidget* parent = nullptr);
  ~SmallExitWindow() override = default;

 signals:
  void StayAtPauseMenu();
  void ReturnToMainMenu();

 private:
  void SetStyles();
  void SetUpLayout();
  void ConnectUI();

  QWidget* main_widget_ = nullptr;
  QGridLayout* grid_layout_ = nullptr;
  QLabel* question_ = nullptr;
  QPushButton* yes_button_ = nullptr;
  QPushButton* no_button_ = nullptr;
};
