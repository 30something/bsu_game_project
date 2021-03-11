#pragma once

#include <QWidget>
#include <QKeyEvent>
#include <QLabel>
#include <QPushButton>
#include <QStackedWidget>
#include <QString>
#include <QStyle>

class SmallExitWindow : public QWidget {
  Q_OBJECT
 public:
  explicit SmallExitWindow(QWidget * = nullptr);
 protected:
  ~SmallExitWindow() override = default;
 private:
  int width_;
  int height_;
  QWidget *main_widget_;
  QLabel *question_;
  QPushButton *yes_button_;
  QPushButton *no_button_;
  friend class PauseMenu;
};

class PauseMenu : public QWidget {
  Q_OBJECT
 public:
  explicit PauseMenu(QWidget * = nullptr);
 protected:
  ~PauseMenu() override = default;
 private:
  int width_;
  int height_;
  QPushButton *settings_button_;
  QPushButton *exit_button_;
  QPushButton *continue_button_;
  SmallExitWindow *small_exit_window_;
  friend class Controller;
};
