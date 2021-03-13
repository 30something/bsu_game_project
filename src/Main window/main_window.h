#pragma once

#include <QMainWindow>
#include <QStackedWidget>
#include <QKeyEvent>

#include "src/Controller/controller.h"
#include "src/Menu/menu.h"

class MainWindow : public QMainWindow {

 public:
  explicit MainWindow(QMainWindow* parent = nullptr);
  ~MainWindow() override = default;

 private:
  void keyPressEvent(QKeyEvent* e) override;
  void keyReleaseEvent(QKeyEvent* e) override;
  void resizeEvent(QResizeEvent*) override;

  QStackedWidget stacked_widget_;
  Controller* controller_;
  Menu* menu_;
  static constexpr int default_screen_width = 800;
  static constexpr int default_screen_height = 800;
};
