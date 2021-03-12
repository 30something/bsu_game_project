#pragma once

#include <QMainWindow>
#include <QStackedWidget>
#include <QKeyEvent>

#include "src/Controller/controller.h"
#include "src/Menu/menu.h"

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
  void resizeEvent(QResizeEvent*) override;

  QStackedWidget stacked_widget_;
  Controller* controller_;
  Menu* menu_;
};
