#include "main_window.h"
#include "src/helpers/sizes.h"

MainWindow::MainWindow(QMainWindow* parent) :
    QMainWindow(parent),
    stacked_widget_(new QStackedWidget(this)),
    menu_(new Menu(this)) {
  setMinimumSize(mainwindow_sizes::kDefaultScreenSize);
  setWindowTitle("Death Rally");
  stacked_widget_->addWidget(menu_);
  stacked_widget_->setCurrentWidget(menu_);

  connect(menu_, &Menu::StartButtonPressed, this,
          &MainWindow::StartGame);
  connect(menu_, &Menu::ExitButtonPressed, this,
          &MainWindow::close);
}

void MainWindow::resizeEvent(QResizeEvent*) {
  stacked_widget_->setGeometry(0, 0, width(), height());
  if (pause_menu_ != nullptr) {
    pause_menu_->setGeometry(0, 0, width(), height());
  }
}

void MainWindow::StartGame() {
  controller_ = new Controller(this);
  pause_menu_ = new PauseMenu(this);
  pause_menu_->setGeometry(0, 0, width(), height());

  connect(controller_, &Controller::SetGamePause, pause_menu_,
          &PauseMenu::show);
  connect(controller_, &Controller::StopGamePause, pause_menu_,
          &PauseMenu::Close);
  connect(pause_menu_, &PauseMenu::ContinueGame, controller_,
          &Controller::SetUnsetPause);
  connect(pause_menu_, &PauseMenu::ReturnToMainMenu, this,
          &MainWindow::ReturnToMainMenu);

  stacked_widget_->addWidget(controller_);
  stacked_widget_->setCurrentWidget(controller_);
}

void MainWindow::ReturnToMainMenu() {
  pause_menu_->close();
  controller_->close();
  stacked_widget_->removeWidget(controller_);
  stacked_widget_->setCurrentWidget(menu_);
  pause_menu_ = nullptr;
  controller_ = nullptr;
  delete controller_;
  delete pause_menu_;
}
