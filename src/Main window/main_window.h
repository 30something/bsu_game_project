#pragma once

#include <QKeyEvent>
#include <QMainWindow>
#include <QStackedWidget>

#include "src/Controller/controller.h"
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
  void keyPressEvent(QKeyEvent*) override;
  void keyReleaseEvent(QKeyEvent*) override;
  void resizeEvent(QResizeEvent*) override;

  QStackedWidget* stacked_widget_;
  Controller* controller_;
  Menu* menu_;
  static constexpr int kDefaultScreenWidth = 800;
  static constexpr int kDefaultScreenHeight = 800;
};
