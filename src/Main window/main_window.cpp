#include "main_window.h"
#include "src/helpers/sizes.h"

MainWindow::MainWindow(QMainWindow* parent) :
    QMainWindow(parent),
    stacked_widget_(new QStackedWidget(this)),
    pause_menu_(new PauseMenu(this)),
    menu_(new Menu(this)),
    game_mode_(new GameMode()),
    game_mode_selector_(new GameModeSelector(this, game_mode_)),
    settings_(new Settings(this)) {
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
  is_game_in_main_menu_ = false;
  events_controller_ = new EventsController(this, game_mode_);
  end_game_stats_ = new EndGameStats(this);
  ConnectGameSignals();
  stacked_widget_->addWidget(events_controller_);
  stacked_widget_->addWidget(end_game_stats_);
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

void MainWindow::ShowEndGameStats() {
  stacked_widget_->setCurrentWidget(end_game_stats_);
}

void MainWindow::ReturnToMainMenu() {
  is_game_in_main_menu_ = true;
  pause_menu_->Close();
  stacked_widget_->removeWidget(events_controller_);
  stacked_widget_->removeWidget(end_game_stats_);
  stacked_widget_->setCurrentWidget(menu_);
  disconnect(pause_menu_, &PauseMenu::ContinueGame, events_controller_,
             &EventsController::SetUnsetPause);
  disconnect(pause_menu_, &PauseMenu::ReturnToMainMenu, this,
             &MainWindow::ReturnToMainMenu);
  delete events_controller_;
  delete end_game_stats_;
  events_controller_ = nullptr;
  end_game_stats_ = nullptr;
}

void MainWindow::OpenMapSelector() {
  stacked_widget_->setCurrentWidget(game_mode_selector_);
}

void MainWindow::CloseMapSelector() {
  stacked_widget_->setCurrentWidget(menu_);
}

void MainWindow::SetUpStackedWidget() {
  stacked_widget_->addWidget(menu_);
  stacked_widget_->addWidget(game_mode_selector_);
  stacked_widget_->addWidget(settings_);
  stacked_widget_->setCurrentWidget(menu_);
}

void MainWindow::ConnectUI() {
  connect(menu_,
          &Menu::StartButtonPressed,
          this,
          &MainWindow::OpenMapSelector);
  connect(game_mode_selector_,
          &GameModeSelector::StartGame,
          this,
          &MainWindow::StartGame);
  connect(game_mode_selector_,
          &GameModeSelector::ReturnToMainMenu,
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
          &MainWindow::ShowEndGameStats);
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
  connect(end_game_stats_,
          &EndGameStats::ReturnToMainMenu,
          this,
          &MainWindow::ReturnToMainMenu);
}
