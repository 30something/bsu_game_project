#include "main_window.h"

MainWindow::MainWindow(QMainWindow* parent) :
    QMainWindow(parent),
    stacked_widget(this),
    view(new View(this)),
    menu(new Menu()) {
  // stacked_widget.addWidget(view);
  // stacked_widget.addWidget(menu);
  // stacked_widget.setCurrentWidget(view);
}

void MainWindow::keyPressEvent(QKeyEvent* event) {
  view->keyPressEvent(event);
}


void MainWindow::keyReleaseEvent(QKeyEvent* event) {
  view->keyReleaseEvent(event);
}