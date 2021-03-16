#include "main_window.h"

MainWindow::MainWindow(QMainWindow* parent) :
    QMainWindow(parent),
    stacked_widget_(new QStackedWidget(this)),
    controller_(new Controller()),
    menu_(new Menu()) {
  setMinimumSize(kDefaultScreenWidth, kDefaultScreenHeight);
  setWindowTitle("Death Rally");
  stacked_widget_->addWidget(controller_);
  stacked_widget_->addWidget(menu_);
  stacked_widget_->setCurrentWidget(menu_);

  connect(menu_->GetStartButton(), &QPushButton::clicked, this,
          &MainWindow::StartGame);
  connect(controller_->GetReturnToMainMenuButton(), &QPushButton::clicked,
          this, &MainWindow::ReturnToMainMenu);
  connect(menu_->GetExitButton(), &QPushButton::clicked, this,
          &MainWindow::ExitGame);
}

void MainWindow::keyPressEvent(QKeyEvent* event) {
  controller_->HandleKeyPressEvent(event);
}

void MainWindow::keyReleaseEvent(QKeyEvent* event) {
  controller_->HandleKeyReleaseEvent(event);
}

void MainWindow::resizeEvent(QResizeEvent*) {
  stacked_widget_->setGeometry(QRect(0, 0, width(), height()));
}

void MainWindow::StartGame() {
  stacked_widget_->setCurrentWidget(controller_);
}

void MainWindow::ExitGame() {
  close();
}

void MainWindow::ReturnToMainMenu() {
  stacked_widget_->setCurrentWidget(menu_);
}
