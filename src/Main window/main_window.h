#pragma once

#include <QKeyEvent>
#include <QMainWindow>
#include <QStackedWidget>

#include "src/EventsController/events_controller.h"
#include "src/Menu/menu.h"
#include "src/Menu/pause_menu.h"
#include "src/Menu/game_mode_selector.h"
#include "src/Menu/settings.h"
#include "src/Network/network_room.h"

class MainWindow : public QMainWindow {
 Q_OBJECT

 public:
  explicit MainWindow(QMainWindow* parent = nullptr);
  ~MainWindow() override = default;

 private:
  void resizeEvent(QResizeEvent*) override;
  void SingleplayerStarted();
  void MultiplayerStarted();

  void SetUpStackedWidget();
  void ConnectUI();
  void ConnectGameSignals();

  void StartGame();
  void ReturnToMainMenu();

  void OpenGameModeSelector();
  void CloseMapSelector();

  void OpenNetworkRoom();
  void CloseNetworkRoom();

  void ShowSettings();
  void HideSettings();

  QStackedWidget* stacked_widget_ = nullptr;
  EventsController* events_controller_ = nullptr;
  PauseMenu* pause_menu_ = nullptr;
  Menu* menu_ = nullptr;
  GameMode* game_mode_ = nullptr;
  GameModeSelector* game_mode_selector_ = nullptr;
  Settings* settings_ = nullptr;
  NetworkRoom* network_room_ = nullptr;
  bool is_game_in_main_menu_ = true;
};
