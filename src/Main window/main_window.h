#pragma once

#include <QKeyEvent>
#include <QMainWindow>
#include <QStackedWidget>

#include "src/Controller/controller.h"
#include "src/Menu/menu.h"
#include "src/Menu/pause_menu.h"
#include "src/Menu/settings.h"

class MainWindow : public QMainWindow {
  Q_OBJECT

 public:
  explicit MainWindow(QMainWindow* parent = nullptr);
  ~MainWindow() override = default;
  void ReturnToMainMenu();
  void StartGame();
  void ShowSettings();
  void HideSettings();

 private:
  void resizeEvent(QResizeEvent*) override;

  QStackedWidget* stacked_widget_;
  Controller* controller_ = nullptr;
  Settings* settings_;
  Menu* menu_;
  PauseMenu* pause_menu_;
};
