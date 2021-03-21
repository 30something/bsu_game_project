#pragma once

#include <QKeyEvent>
#include <QMainWindow>
#include <QStackedWidget>

#include "src/Controller/controller.h"
#include "src/Menu/menu.h"
#include "src/Menu/pause_menu.h"

class MainWindow : public QMainWindow {
  Q_OBJECT

 public:
  explicit MainWindow(QMainWindow* parent = nullptr);
  ~MainWindow() override = default;
  void ReturnToMainMenu();
  void StartGame();

 protected:
  void resizeEvent(QResizeEvent*) override;

 private:
  QStackedWidget* stacked_widget_;
  Controller* controller_ = nullptr;
  PauseMenu* pause_menu_ = nullptr;
  Menu* menu_;
};
