#include "main_window.h"

MainWindow::MainWindow(QMainWindow* parent) :
    QMainWindow(parent),
    stacked_widget_(new QStackedWidget(this)),
    controller_(new Controller()),
    menu_(new Menu()) {
  setMinimumSize(kDefaultScreenWidth, kDefaultScreenHeight);
  setWindowTitle("Death Rally");
  stacked_widget_->resize(kDefaultScreenWidth, kDefaultScreenHeight);
  controller_->resize(kDefaultScreenWidth, kDefaultScreenHeight);
  stacked_widget_->addWidget(controller_);
  stacked_widget_->addWidget(menu_);
  stacked_widget_->setCurrentWidget(menu_);

  connect(menu_->GetStartButton(), &QPushButton::clicked, this,
          &MainWindow::StartGame);
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
  controller_->setGeometry(QRect(0, 0, width(), height()));
}

void MainWindow::StartGame() {
  stacked_widget_->setCurrentWidget(controller_);
}

void MainWindow::ExitGame() {
  close();
}
