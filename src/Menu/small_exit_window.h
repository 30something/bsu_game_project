#pragma once

#include <QLabel>
#include <QPushButton>
#include <QSize>
#include <QWidget>

class SmallExitWindow : public QWidget {
 public:
  explicit SmallExitWindow(QWidget* parent = nullptr);
  ~SmallExitWindow() override = default;

 private:
  QWidget* main_widget_;
  QLabel* question_;
  QPushButton* yes_button_;
  QPushButton* no_button_;
  int width_ = 250;
  int height_ = 100;
  friend class PauseMenu;
};
