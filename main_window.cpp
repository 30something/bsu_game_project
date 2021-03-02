#include "main_window.h"

MainWindow::MainWindow(QMainWindow* parent) :
    QMainWindow(parent),
    stacked_widget(this),
    view(new View()),
    menu(new Menu()) {
  resize(800,800);
  stacked_widget.resize(800,800);
  stacked_widget.addWidget(view);
  stacked_widget.addWidget(menu);
  stacked_widget.setCurrentWidget(view);
}

void MainWindow::keyPressEvent(QKeyEvent* event) {
  view->keyPressEvent(event);
}


void MainWindow::keyReleaseEvent(QKeyEvent* event) {
  view->keyReleaseEvent(event);
}