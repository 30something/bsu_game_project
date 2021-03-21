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
  QWidget* main_widget_;
  QGridLayout* grid_layout_;
  QLabel* question_;
  QPushButton* yes_button_;
  QPushButton* no_button_;
};
