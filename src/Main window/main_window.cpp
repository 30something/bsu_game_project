#include "main_window.h"
#include "src/helpers/sizes.h"

MainWindow::MainWindow(QMainWindow* parent) :
    QMainWindow(parent),
    stacked_widget_(new QStackedWidget(this)),
    pause_menu_(new PauseMenu(this)),
    menu_(new Menu(this)),
    game_mode_(new GameMode()),
    game_mode_selector_(new GameModeSelector(this, game_mode_)){
  setMinimumSize(mainwindow_sizes::kDefaultScreenSize);
  setWindowTitle("Death Rally");
  stacked_widget_->addWidget(menu_);
  stacked_widget_->addWidget(game_mode_selector_);
  stacked_widget_->setCurrentWidget(menu_);
  pause_menu_->Close();

  connect(menu_, &Menu::StartButtonPressed, this,
          &MainWindow::OpenMapSelector);
  connect(game_mode_selector_, &GameModeSelector::StartGame, this,
          &MainWindow::StartGame);
  connect(game_mode_selector_, &GameModeSelector::ReturnToMainMenu, this,
          &MainWindow::CloseMapSelector);
  connect(menu_, &Menu::ExitButtonPressed, this,
          &MainWindow::close);
}

void MainWindow::resizeEvent(QResizeEvent*) {
  stacked_widget_->setGeometry(0, 0, width(), height());
  pause_menu_->setGeometry(0, 0, width(), height());
}

void MainWindow::StartGame() {
  events_controller_ = new EventsController(this, game_mode_);

  connect(events_controller_, &EventsController::SetGamePause, pause_menu_,
          &PauseMenu::show);
  connect(events_controller_, &EventsController::StopGamePause, pause_menu_,
          &PauseMenu::Close);
  connect(pause_menu_, &PauseMenu::ContinueGame, events_controller_,
          &EventsController::SetUnsetPause);
  connect(pause_menu_, &PauseMenu::ReturnToMainMenu, this,
          &MainWindow::ReturnToMainMenu);

  stacked_widget_->addWidget(events_controller_);
  stacked_widget_->setCurrentWidget(events_controller_);
}

void MainWindow::ReturnToMainMenu() {
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
