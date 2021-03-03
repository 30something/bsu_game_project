#include "main_window.h"

MainWindow::MainWindow(QMainWindow* parent) :
    QMainWindow(parent),
    stacked_widget_(this),
    view_(new View()),
    menu_(new Menu()) {
  resize(800, 800);
  stacked_widget_.resize(800, 800);
  stacked_widget_.addWidget(view_);
  stacked_widget_.addWidget(menu_);
  stacked_widget_.setCurrentWidget(view_);
}

void MainWindow::keyPressEvent(QKeyEvent* event) {
  view_->keyPressEvent(event);
}

void MainWindow::keyReleaseEvent(QKeyEvent* event) {
  view_->keyReleaseEvent(event);
}
