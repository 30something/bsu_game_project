#include "main_window.h"

MainWindow::MainWindow(QMainWindow* parent) :
    QMainWindow(parent),
    stacked_widget_(this),
    controller_(new Controller()),
    menu_(new Menu()) {
  resize(default_screen_width, default_screen_height);
  stacked_widget_.resize(default_screen_width, default_screen_height);
  controller_->resize(default_screen_width, default_screen_height);
  stacked_widget_.addWidget(controller_);
  stacked_widget_.addWidget(menu_);
  stacked_widget_.setCurrentWidget(controller_);
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
