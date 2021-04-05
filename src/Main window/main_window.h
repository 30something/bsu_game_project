#pragma once

#include <QKeyEvent>
#include <QMainWindow>
#include <QStackedWidget>

#include "src/EventsController/EventsController.h"
#include "src/Menu/menu.h"
#include "src/Menu/pause_menu.h"
#include "src/Menu/game_mode_selector.h"
#include "src/Menu/settings.h"

class MainWindow : public QMainWindow {
  Q_OBJECT

 public:
  explicit MainWindow(QMainWindow* parent = nullptr);
  ~MainWindow() override = default;

 private:
  void resizeEvent(QResizeEvent*) override;

  void SetUpStackedWidget();
  void ConnectUI();
  void ConnectGameSignals();

  void StartGame();
  void ReturnToMainMenu();

  void OpenMapSelector();
  void CloseMapSelector();

  void ShowSettings();
  void HideSettings();

  QStackedWidget* stacked_widget_ = nullptr;
  EventsController* events_controller_ = nullptr;
  PauseMenu* pause_menu_ = nullptr;
  Menu* menu_ = nullptr;
  GameMode* game_mode_ = nullptr;
  GameModeSelector* game_mode_selector_ = nullptr;
  Settings* settings_ = nullptr;
  bool is_game_in_main_menu = true;
};
