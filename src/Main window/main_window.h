#pragma once

#include <QKeyEvent>
#include <QMainWindow>
#include <QStackedWidget>

#include "src/Controller/EventsController.h"
#include "src/Menu/menu.h"

class MainWindow : public QMainWindow {
  Q_OBJECT

 public:
  explicit MainWindow(QMainWindow* parent = nullptr);
  ~MainWindow() override = default;
  void StartGame();
  void ExitGame();
  void ReturnToMainMenu();

 private:
  void resizeEvent(QResizeEvent*) override;

  QStackedWidget* stacked_widget_;
  Controller* controller_ = nullptr;
  Menu* menu_;
};
