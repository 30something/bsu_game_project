#include "main_window.h"

MainWindow::MainWindow(QMainWindow *parent) :
    QMainWindow(parent),
    stacked_widget_(this),
    controller_(new Controller()),
    menu_(new Menu()) {
  resize(screen_width_, screen_height_);
  stacked_widget_.resize(screen_width_, screen_height_);
  controller_->resize(screen_width_, screen_height_);
  stacked_widget_.addWidget(controller_);
  stacked_widget_.addWidget(menu_);
  stacked_widget_.setCurrentWidget(controller_);
}

void MainWindow::keyPressEvent(QKeyEvent *event) {
  controller_->HandleKeyPressEvent(event);
}

void MainWindow::keyReleaseEvent(QKeyEvent *event) {
  controller_->HandleKeyReleaseEvent(event);
}
