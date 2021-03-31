#include "main_window.h"
#include "src/helpers/sizes.h"

MainWindow::MainWindow(QMainWindow* parent) :
    QMainWindow(parent),
    stacked_widget_(new QStackedWidget(this)),
    pause_menu_(new PauseMenu(this)),
    menu_(new Menu(this)),
    game_mode_(new GameMode()),
    game_mode_selector_(new GameModeSelector(this, game_mode_)){
    settings_(new Settings(this)){
  setMinimumSize(mainwindow_sizes::kDefaultScreenSize);
  setWindowTitle("Death Rally");
  SetUpStackedWidget();
  pause_menu_->Close();
  ConnectUI();
}

void MainWindow::resizeEvent(QResizeEvent*) {
  stacked_widget_->setGeometry(0, 0, width(), height());
  pause_menu_->setGeometry(0, 0, width(), height());
}

void MainWindow::StartGame() {
  is_game_in_main_menu = false;
  events_controller_ = new EventsController(this, map_selector_->GetMapId());
  ConnectGameSignals();
  stacked_widget_->addWidget(events_controller_);
  stacked_widget_->setCurrentWidget(events_controller_);
    stacked_widget_->addWidget(events_controller_);
  stacked_widget_->setCurrentWidget(events_controller_);}

void MainWindow::ShowSettings() {
  stacked_widget_->setCurrentWidget(settings_);
  pause_menu_->Close();
}

void MainWindow::HideSettings() {
  if (is_game_in_main_menu) {
    stacked_widget_->setCurrentWidget(menu_);
  } else {
    stacked_widget_->setCurrentWidget(controller_);
    pause_menu_->show();
  }
}

void MainWindow::ReturnToMainMenu() {
  is_game_in_main_menu = true;
  pause_menu_->Close();
  stacked_widget_->removeWidget(events_controller_);
  stacked_widget_->setCurrentWidget(menu_);
  disconnect(pause_menu_, &PauseMenu::ContinueGame, events_controller_,
             &EventsController::SetUnsetPause);
  disconnect(pause_menu_, &PauseMenu::ReturnToMainMenu, this,
             &MainWindow::ReturnToMainMenu);
  delete events_controller_;
  events_controller_ = nullptr;
}

void MainWindow::OpenMapSelector() {
  stacked_widget_->setCurrentWidget(game_mode_selector_);
}

void MainWindow::CloseMapSelector() {
  stacked_widget_->setCurrentWidget(menu_);
}

void MainWindow::SetUpStackedWidget() {
  stacked_widget_->addWidget(menu_);
  stacked_widget_->addWidget(map_selector_);
  stacked_widget_->addWidget(settings_);
  stacked_widget_->setCurrentWidget(menu_);
}

void MainWindow::ConnectUI() {
  connect(menu_,
          &Menu::StartButtonPressed,
          this,
          &MainWindow::OpenMapSelector);
  connect(map_selector_,
          &MapSelector::StartGame,
          this,
          &MainWindow::StartGame);
  connect(map_selector_,
          &MapSelector::ReturnToMainMenu,
          this,
          &MainWindow::CloseMapSelector);
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
  connect(controller_,
          &EventsController::SetGamePause,
          pause_menu_,
          &PauseMenu::show);
  connect(controller_,
          &EventsController::StopGamePause,
          pause_menu_,
          &PauseMenu::Close);
  connect(pause_menu_,
          &PauseMenu::ContinueGame,
          controller_,
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
