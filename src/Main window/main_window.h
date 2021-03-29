#pragma once

#include <QKeyEvent>
#include <QMainWindow>
#include <QStackedWidget>

#include "src/EventsController/EventsController.h"
#include "src/Menu/menu.h"
#include "src/Menu/pause_menu.h"
#include "src/Menu/settings.h"
#include "src/Menu/map_selector.h"

class MainWindow : public QMainWindow {
  Q_OBJECT

 public:
  explicit MainWindow(QMainWindow* parent = nullptr);
  ~MainWindow() override = default;

 private:
  void resizeEvent(QResizeEvent*) override;

  void MakeStackedWidget();
  void DoConnects();
  void DoStartGameConnects();

  void StartGame();
  void ReturnToMainMenu();

  void OpenMapSelector();
  void CloseMapSelector();

  void ShowSettings();
  void HideSettings();

  QStackedWidget* stacked_widget_ = nullptr;
  EventsController* controller_ = nullptr;
  PauseMenu* pause_menu_ = nullptr;
  Menu* menu_ = nullptr;
  Settings* settings_ = nullptr;
  MapSelector* map_selector_ = nullptr;
};
