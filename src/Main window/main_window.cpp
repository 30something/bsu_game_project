#include "main_window.h"

MainWindow::MainWindow(QMainWindow* parent) :
    QMainWindow(parent),
    stacked_widget_(new QStackedWidget(this)),
    pause_menu_(new PauseMenu(this)),
    menu_(new Menu(this)),
    game_mode_(new GameMode()),
    game_mode_selector_(new GameModeSelector(this, game_mode_)),
    settings_(new Settings(game_mode_, this)),
    network_room_(new NetworkRoom(this, game_mode_)),
    credits_(new Credits(this)) {
  setMinimumSize(mainwindow_sizes::kDefaultScreenSize);
  setWindowTitle("Survival Rally: Big Guns");
  setWindowIcon(QIcon(":resources/images/other_stuff/icon0.png"));
  SetUpStackedWidget();
  pause_menu_->Close();
  background_.load(":resources/images/other_stuff/background.png");
  ConnectUI();
}

void MainWindow::resizeEvent(QResizeEvent*) {
  stacked_widget_->setGeometry(0, 0, width(), height());
  pause_menu_->setGeometry(0, 0, width(), height());
  QPixmap scaled_background =
      background_.scaled(width(), height(), Qt::IgnoreAspectRatio);
  QPalette palette;
  palette.setBrush(QPalette::Window, scaled_background);
  setPalette(palette);
}

void MainWindow::StartGame() {
  is_game_in_main_menu_ = false;
  events_controller_ = new EventsController(this, game_mode_);
  ConnectGameSignals();
  stacked_widget_->addWidget(events_controller_);
  stacked_widget_->setCurrentWidget(events_controller_);
}

void MainWindow::ShowSettings() {
  stacked_widget_->setCurrentWidget(settings_);
  pause_menu_->Close();
}

void MainWindow::HideSettings() {
  if (is_game_in_main_menu_) {
    stacked_widget_->setCurrentWidget(menu_);
  } else {
    stacked_widget_->setCurrentWidget(events_controller_);
    pause_menu_->show();
  }
}

void MainWindow::ShowCredits() {
  stacked_widget_->setCurrentWidget(credits_);
}

void MainWindow::CloseCredits() {
  stacked_widget_->setCurrentWidget(menu_);
}

void MainWindow::ReturnToMainMenu() {
  is_game_in_main_menu_ = true;
  pause_menu_->Close();
  stacked_widget_->removeWidget(events_controller_);
  stacked_widget_->setCurrentWidget(menu_);
  disconnect(pause_menu_, &PauseMenu::ContinueGame, events_controller_,
             &EventsController::SetUnsetPause);
  disconnect(pause_menu_, &PauseMenu::ReturnToMainMenu, this,
             &MainWindow::ReturnToMainMenu);
  delete events_controller_;
  events_controller_ = nullptr;
  if (game_mode_->network_controller != nullptr) {
    game_mode_->network_controller->SetAlreadyStarted(false);
  }
}

void MainWindow::OpenGameModeSelector() {
  stacked_widget_->setCurrentWidget(game_mode_selector_);
}

void MainWindow::CloseMapSelector() {
  stacked_widget_->setCurrentWidget(menu_);
}

void MainWindow::OpenNetworkRoom() {
  stacked_widget_->setCurrentWidget(network_room_);
}

void MainWindow::CloseNetworkRoom() {
  stacked_widget_->setCurrentWidget(menu_);
}

void MainWindow::SingleplayerStarted() {
  game_mode_selector_->SetSingleplayer(true);
}

void MainWindow::MultiplayerStarted() {
  game_mode_selector_->SetSingleplayer(false);
}

void MainWindow::SetUpStackedWidget() {
  stacked_widget_->addWidget(menu_);
  stacked_widget_->addWidget(game_mode_selector_);
  stacked_widget_->addWidget(settings_);
  stacked_widget_->addWidget(network_room_);
  stacked_widget_->addWidget(credits_);
  stacked_widget_->setCurrentWidget(menu_);
}

void MainWindow::ConnectUI() {
  connect(menu_,
          &Menu::SinglePlayerPressed,
          this,
          &MainWindow::SingleplayerStarted);
  connect(menu_,
          &Menu::MultiPlayerPressed,
          this,
          &MainWindow::MultiplayerStarted);
  connect(menu_,
          &Menu::SinglePlayerPressed,
          this,
          &MainWindow::OpenGameModeSelector);
  connect(menu_,
          &Menu::MultiPlayerPressed,
          this,
          &MainWindow::OpenNetworkRoom);
  connect(menu_,
          &Menu::CreditsButtonPressed,
          this,
          &MainWindow::ShowCredits);
  connect(credits_,
          &Credits::ReturnToMainMenu,
          this,
          &MainWindow::CloseCredits);
  connect(game_mode_selector_,
          &GameModeSelector::StartGame,
          this,
          &MainWindow::StartGame);
  connect(game_mode_selector_,
          &GameModeSelector::ReturnToMainMenu,
          this,
          &MainWindow::CloseMapSelector);
  connect(network_room_,
          &NetworkRoom::ReturnToMainMenu,
          this,
          &MainWindow::CloseNetworkRoom);
  connect(network_room_,
          &NetworkRoom::StartGame,
          this,
          &MainWindow::StartGame);
  connect(network_room_,
          &NetworkRoom::OpenGameModeSelector,
          this,
          &MainWindow::OpenGameModeSelector);
  connect(network_room_,
          &NetworkRoom::ExitDisconnected,
          this,
          &MainWindow::ReturnToMainMenu);
  connect(menu_,
          &Menu::SettingsButtonPressed,
          this,
          &MainWindow::ShowSettings);
  connect(settings_,
          &Settings::MakeFullScreen,
          this,
          &MainWindow::showFullScreen);
  connect(settings_,
          &Settings::MakeDefaultScreenSize,
          this,
          &MainWindow::showNormal);
  connect(settings_,
          &Settings::BackButtonPressed,
          this,
          &MainWindow::HideSettings);
  connect(menu_,
          &Menu::ExitButtonPressed,
          this,
          &MainWindow::close);
}

void MainWindow::ConnectGameSignals() {
  connect(events_controller_,
          &EventsController::SetGamePause,
          pause_menu_,
          &PauseMenu::show);
  connect(events_controller_,
          &EventsController::StopGamePause,
          pause_menu_,
          &PauseMenu::Close);
  connect(events_controller_,
          &EventsController::ReturnToMainMenu,
          this,
          &MainWindow::ReturnToMainMenu);
  connect(pause_menu_,
          &PauseMenu::ContinueGame,
          events_controller_,
          &EventsController::SetUnsetPause);
  connect(pause_menu_,
          &PauseMenu::ReturnToMainMenu,
          this,
          &MainWindow::ReturnToMainMenu);
  connect(pause_menu_,
          &PauseMenu::ShowSettingsFromPM,
          this,
          &MainWindow::ShowSettings);
  connect(settings_,
          &Settings::BackButtonPressed,
          this,
          &MainWindow::HideSettings);
}
