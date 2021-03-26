#pragma once

#include <QGridLayout>
#include <QLabel>
#include <QPushButton>
#include <QSize>
#include <QWidget>

class SmallExitWindow : public QWidget {
  Q_OBJECT

 public:
  explicit SmallExitWindow(QWidget* parent = nullptr);
  ~SmallExitWindow() override = default;

 signals:
  void StayAtPauseMenu();
  void ReturnToMainMenu();

 private:
  QWidget* main_widget_ = nullptr;
  QGridLayout* grid_layout_ = nullptr;
  QLabel* question_ = nullptr;
  QPushButton* yes_button_ = nullptr;
  QPushButton* no_button_ = nullptr;
};
