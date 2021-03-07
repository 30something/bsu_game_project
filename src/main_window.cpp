#include "main_window.h"

MainWindow::MainWindow(QMainWindow* parent) :
    QMainWindow(parent),
    stacked_widget_(this),
    controller_(new Controller()),
    menu_(new Menu()) {
  resize(800, 800);
  stacked_widget_.resize(800, 800);
  controller_->resize(800, 800);
  stacked_widget_.addWidget(controller_);
  stacked_widget_.addWidget(menu_);
  stacked_widget_.setCurrentWidget(controller_);
}

void MainWindow::keyPressEvent(QKeyEvent* event) {
  controller_->KeyPressEvent(event);
}

void MainWindow::keyReleaseEvent(QKeyEvent* event) {
  controller_->KeyReleaseEvent(event);
}
