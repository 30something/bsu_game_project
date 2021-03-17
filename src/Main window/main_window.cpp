#include "main_window.h"

MainWindow::MainWindow(QMainWindow* parent) :
    QMainWindow(parent),
    stacked_widget_(new QStackedWidget(this)),
    menu_(new Menu(this)) {
  setMinimumSize(kDefaultScreenWidth, kDefaultScreenHeight);
  setWindowTitle("Death Rally");
  stacked_widget_->addWidget(menu_);
  stacked_widget_->setCurrentWidget(menu_);

  connect(menu_->GetStartButton(), &QPushButton::clicked, this,
          &MainWindow::StartGame);
  connect(menu_->GetExitButton(), &QPushButton::clicked, this,
          &MainWindow::ExitGame);
}

void MainWindow::keyPressEvent(QKeyEvent* event) {
  if (controller_ != nullptr) {
    controller_->HandleKeyPressEvent(event);
  }
}

void MainWindow::keyReleaseEvent(QKeyEvent* event) {
  if (controller_ != nullptr) {
    controller_->HandleKeyReleaseEvent(event);
  }
}

void MainWindow::resizeEvent(QResizeEvent*) {
  stacked_widget_->setGeometry(0, 0, width(), height());
}

void MainWindow::StartGame() {
  controller_ = new Controller(this);
  connect(controller_->GetReturnToMainMenuButton(), &QPushButton::clicked,
          this, &MainWindow::ReturnToMainMenu);
  stacked_widget_->addWidget(controller_);
  stacked_widget_->setCurrentWidget(controller_);
}

void MainWindow::ExitGame() {
  close();
}

void MainWindow::ReturnToMainMenu() {
  stacked_widget_->removeWidget(controller_);
  stacked_widget_->setCurrentWidget(menu_);
}
