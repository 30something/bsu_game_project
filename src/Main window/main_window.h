#pragma once

#include <QKeyEvent>
#include <QMainWindow>
#include <QStackedWidget>

#include "src/EventsController/EventsController.h"
#include "src/Menu/menu.h"
#include "src/Menu/pause_menu.h"

class MainWindow : public QMainWindow {
 Q_OBJECT

 public:
  explicit MainWindow(QMainWindow* parent = nullptr);
  ~MainWindow() override = default;
  void ReturnToMainMenu();
  void StartGame();

 private:
  void resizeEvent(QResizeEvent*) override;

  QStackedWidget* stacked_widget_;
  EventsController* controller_ = nullptr;
  PauseMenu* pause_menu_;
  Menu* menu_;
};
