#pragma once

#include <QMainWindow>
#include <QStackedWidget>
#include <QKeyEvent>

#include "view.h"
#include "menu.h"

class MainWindow : public QMainWindow {
 Q_OBJECT

 public:
  explicit MainWindow(QMainWindow* parent = nullptr);
  ~MainWindow() override = default;

 private:
  void keyPressEvent(QKeyEvent* e) override;
  void keyReleaseEvent(QKeyEvent* e) override;
  QStackedWidget stacked_widget;
  View* view;
  Menu* menu;
};
