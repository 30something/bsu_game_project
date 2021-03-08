#pragma once

#include <QMainWindow>
#include <QStackedWidget>
#include <QKeyEvent>

#include "src/controller.h"
#include "menu.h"

class MainWindow : public QMainWindow {
  Q_OBJECT

 public:
  explicit MainWindow(QMainWindow* parent = nullptr);
  ~MainWindow() override = default;

 private:
  int screen_width_ = 800;
  int screen_height_ = 800;

  void keyPressEvent(QKeyEvent* e) override;
  void keyReleaseEvent(QKeyEvent* e) override;

  QStackedWidget stacked_widget_;
  Controller* controller_;
  Menu* menu_;
};
